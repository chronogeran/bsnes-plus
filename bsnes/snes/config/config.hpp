struct Configuration {
  Input::Device controller_port1;
  Input::Device controller_port2;
  System::ExpansionPortDevice expansion_port;
  unsigned vram_size;
  System::Region region;
  bool random;
  SNES::SMP::SPCSavePolicy spc_save_policy;

  struct CPU {
    unsigned version;
    unsigned ntsc_frequency;
    unsigned pal_frequency;
    unsigned wram_init_value;
  } cpu;

  struct SMP {
    unsigned ntsc_frequency;
    unsigned pal_frequency;
  } smp;

  struct PPU1 {
    unsigned version;
  } ppu1;

  struct PPU2 {
    unsigned version;
  } ppu2;

  struct Path {
    string firmware;
    string bsxdat;
  } path;

  struct Satellaview {
    bool local_time;
    time_t custom_time;
    unsigned default_size;
  } sat;

  Configuration();
};

Configuration &config();
