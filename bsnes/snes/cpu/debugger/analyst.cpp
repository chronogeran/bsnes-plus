#ifdef CPU_CPP

// ------------------------------------------------------------------------
void CPUAnalyst::performFullAnalysis() {
  performAnalysisForVector(0xFFE4);
  performAnalysisForVector(0xFFE6);
  performAnalysisForVector(0xFFE8);
  performAnalysisForVector(0xFFEA);
  performAnalysisForVector(0xFFEE);

  performAnalysisForVector(0xFFF4, true);
  performAnalysisForVector(0xFFF8, true);
  performAnalysisForVector(0xFFFA, true);
  performAnalysisForVector(0xFFFC, true);
  performAnalysisForVector(0xFFFE, true);
}

// ------------------------------------------------------------------------
void CPUAnalyst::performAnalysisForVector(uint32_t address, bool emulation) {
  uint16_t vectorAddr = cpu.dreadw(address);
  if (vectorAddr >= 0x8000) {
    CPUAnalystState state(emulation);
    uint32_t numRoutines = performAnalysis(vectorAddr, state);

    //puts(string("Found ", numRoutines, " new symbols at vector $", hex<6,'0'>(address)));
  }
}

// ------------------------------------------------------------------------
uint32_t CPUAnalyst::performAnalysis(uint32_t address, CPUAnalystState &state, bool force) {
  if (usage[address] != 0 && !force) {
    return 0;
  }

  CPUDebugger::Opcode op;
  linear_vector<CPUAnalystState> stackP;
  uint32_t maxMethodSize = 0x1000;
  uint32_t numRoutines = 1;

  while (--maxMethodSize) {
    address = address & 0xFFFFFF;
    if (usage[address] != 0 && !force) {
      break;
    }

    usage[address] |= CPUDebugger::UsageOpcode | state.mask();
    core.disassemble_opcode_ex(op, address, state.e, state.m, state.x);

    if (op.setsX()) { state.x = true; }
    if (op.setsM()) { state.m = true; }
    if (op.resetsX()) { state.x = false; }
    if (op.resetsM()) { state.m = false; }
    if (op.resetsE()) { state.e = false; }

    if (op.pushesP()) {
      stackP.append(state);
    }
    if (op.popsP() && stackP.size()) {
      uint32_t index = stackP.size() - 1;
      state = stackP[index];
      stackP.remove(index);
    }

    if (op.breaks() || op.halts()) {
      break;
    }

    if (op.isCall()) {
      // analyze the call target, preserving any state changes inside the subroutine
      numRoutines += performAnalysis(core.decode(op.optype, op.opall(), address), state);
    } else if (op.isBraWithContinue() && !op.isIndirect()) {
      // analyze the branch target, not preserving any state changes from when the branch is taken
      CPUAnalystState tempState(state);
      numRoutines += performAnalysis(core.decode(op.optype, op.opall(), address), tempState);
    }

    if (op.isBra() && !op.isIndirect()) {
      address = core.decode(op.optype, op.opall(), address);
      numRoutines++;
      force = false; // we might be branching/jumping into already analyzed code
    } else if (op.returns() || op.isBra()) {
      break;
    } else {
      address += op.size();
    }
  }

  return numRoutines;
}

#endif
