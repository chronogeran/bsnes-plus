#include "advanced.moc"
AdvancedSettingsWindow *advancedSettingsWindow;

AdvancedSettingsWindow::AdvancedSettingsWindow() {
  layout = new QVBoxLayout;
  layout->setMargin(Style::WindowMargin);
  layout->setSpacing(0);
  layout->setAlignment(Qt::AlignTop);
  setLayout(layout);

  driverLayout = new QGridLayout;
  driverLayout->setHorizontalSpacing(Style::WidgetSpacing);
  layout->addLayout(driverLayout);
  layout->addSpacing(Style::WidgetSpacing);

  videoLabel = new QLabel("Video driver:");
  driverLayout->addWidget(videoLabel, 0, 0);

  audioLabel = new QLabel("Audio driver:");
  driverLayout->addWidget(audioLabel, 0, 1);

  inputLabel = new QLabel("Input driver:");
  driverLayout->addWidget(inputLabel, 0, 2);

  videoDriver = new QComboBox;
  driverLayout->addWidget(videoDriver, 1, 0);

  audioDriver = new QComboBox;
  driverLayout->addWidget(audioDriver, 1, 1);

  inputDriver = new QComboBox;
  driverLayout->addWidget(inputDriver, 1, 2);

  driverInfo = new QLabel("<small>Note: driver changes require restart to take effect.</small>");
  driverInfo->setStyleSheet("margin-left: -3px; margin-top: 5px;");
  driverLayout->addWidget(driverInfo, 2, 0, 1, 3);

  regionTitle = new QLabel("Hardware region:");
  layout->addWidget(regionTitle);

  regionLayout = new QHBoxLayout;
  regionLayout->setSpacing(Style::WidgetSpacing);
  layout->addLayout(regionLayout);
  layout->addSpacing(Style::WidgetSpacing);

  regionGroup = new QButtonGroup(this);

  regionAuto = new QRadioButton("Auto-detect");
  regionAuto->setToolTip("Automatically select hardware region on cartridge load");
  regionGroup->addButton(regionAuto);
  regionLayout->addWidget(regionAuto);

  regionNTSC = new QRadioButton("NTSC");
  regionNTSC->setToolTip("Force NTSC region (Japan, Korea, US)");
  regionGroup->addButton(regionNTSC);
  regionLayout->addWidget(regionNTSC);

  regionPAL = new QRadioButton("PAL");
  regionPAL->setToolTip("Force PAL region (Europe, ...)");
  regionGroup->addButton(regionPAL);
  regionLayout->addWidget(regionPAL);

  portTitle = new QLabel("Expansion port device:");
  layout->addWidget(portTitle);

  portLayout = new QHBoxLayout;
  portLayout->setSpacing(Style::WidgetSpacing);
  layout->addLayout(portLayout);
  layout->addSpacing(Style::WidgetSpacing);

  portGroup = new QButtonGroup(this);

  portSatellaview = new QRadioButton("Satellaview");
  portGroup->addButton(portSatellaview);
  portLayout->addWidget(portSatellaview);

  portNone = new QRadioButton("None");
  portGroup->addButton(portNone);
  portLayout->addWidget(portNone);

  portLayout->addWidget(new QWidget); // spacer

  vramTitle = new QLabel("VRAM size:");
  layout->addWidget(vramTitle);

  vramLayout = new QHBoxLayout;
  vramLayout->setSpacing(Style::WidgetSpacing);
  layout->addLayout(vramLayout);
  layout->addSpacing(Style::WidgetSpacing);

  vramGroup = new QButtonGroup(this);

  vram64kb = new QRadioButton("64 kb (no expansion)");
  vramGroup->addButton(vram64kb);
  vramLayout->addWidget(vram64kb);

  vram128kb = new QRadioButton("128 kb");
  vramGroup->addButton(vram128kb);
  vramLayout->addWidget(vram128kb);

  vram256kb = new QRadioButton("256 kb");
  vramGroup->addButton(vram256kb);
  vramLayout->addWidget(vram256kb);

  focusTitle = new QLabel("When main window does not have focus:");
  layout->addWidget(focusTitle);

  focusLayout = new QHBoxLayout;
  focusLayout->setSpacing(Style::WidgetSpacing);
  layout->addLayout(focusLayout);
  layout->addSpacing(Style::WidgetSpacing);

  focusButtonGroup = new QButtonGroup(this);

  focusPause = new QRadioButton("Pause emulation");
  focusPause->setToolTip("Ideal for prolonged multi-tasking");
  focusButtonGroup->addButton(focusPause);
  focusLayout->addWidget(focusPause);

  focusIgnore = new QRadioButton("Ignore input");
  focusIgnore->setToolTip("Ideal for light multi-tasking when using keyboard");
  focusButtonGroup->addButton(focusIgnore);
  focusLayout->addWidget(focusIgnore);

  focusAllow = new QRadioButton("Allow input");
  focusAllow->setToolTip("Ideal for light multi-tasking when using joypad(s)");
  focusButtonGroup->addButton(focusAllow);
  focusLayout->addWidget(focusAllow);

  saveSPCTitle = new QLabel("Save SPC file:");
  layout->addWidget(saveSPCTitle);

  saveSPCLayout = new QHBoxLayout;
  saveSPCLayout->setSpacing(Style::WidgetSpacing);
  layout->addLayout(saveSPCLayout);
  layout->addSpacing(Style::WidgetSpacing);

  saveSPCButtonGroup = new QButtonGroup(this);

  saveSPCOnNextNote = new QRadioButton("At start of next note");
  saveSPCOnNextNote->setToolTip("Typical use-case");
  saveSPCButtonGroup->addButton(saveSPCOnNextNote);
  saveSPCLayout->addWidget(saveSPCOnNextNote);

  saveSPCImmediately = new QRadioButton("Immediately");
  saveSPCImmediately->setToolTip("Useful for debugging");
  saveSPCButtonGroup->addButton(saveSPCImmediately);
  saveSPCLayout->addWidget(saveSPCImmediately);
  
  saveSPCLayout->addWidget(new QWidget); // spacer
  
  miscTitle = new QLabel("Miscellaneous:");
  layout->addWidget(miscTitle);

  autoSaveEnable = new QCheckBox("Auto-save SRAM once every minute");
  layout->addWidget(autoSaveEnable);
  
  rewindEnable = new QCheckBox("Enable rewind support");
  layout->addWidget(rewindEnable);

  allowInvalidInput = new QCheckBox("Allow up+down / left+right combinations");
  layout->addWidget(allowInvalidInput);

  useCommonDialogs = new QCheckBox("Use native OS file dialogs");
  layout->addWidget(useCommonDialogs);

  initializeUi();

  connect(videoDriver, SIGNAL(currentIndexChanged(int)), this, SLOT(videoDriverChange(int)));
  connect(audioDriver, SIGNAL(currentIndexChanged(int)), this, SLOT(audioDriverChange(int)));
  connect(inputDriver, SIGNAL(currentIndexChanged(int)), this, SLOT(inputDriverChange(int)));
  connect(regionAuto, SIGNAL(pressed()), this, SLOT(setRegionAuto()));
  connect(regionNTSC, SIGNAL(pressed()), this, SLOT(setRegionNTSC()));
  connect(regionPAL, SIGNAL(pressed()), this, SLOT(setRegionPAL()));
  connect(portSatellaview, SIGNAL(pressed()), this, SLOT(setPortSatellaview()));
  connect(portNone, SIGNAL(pressed()), this, SLOT(setPortNone()));
  connect(focusPause, SIGNAL(pressed()), this, SLOT(pauseWithoutFocus()));
  connect(focusIgnore, SIGNAL(pressed()), this, SLOT(ignoreInputWithoutFocus()));
  connect(focusAllow, SIGNAL(pressed()), this, SLOT(allowInputWithoutFocus()));
  connect(autoSaveEnable, SIGNAL(stateChanged(int)), this, SLOT(toggleAutoSaveEnable()));
  connect(rewindEnable, SIGNAL(stateChanged(int)), this, SLOT(toggleRewindEnable()));
  connect(allowInvalidInput, SIGNAL(stateChanged(int)), this, SLOT(toggleAllowInvalidInput()));
  connect(useCommonDialogs, SIGNAL(stateChanged(int)), this, SLOT(toggleUseCommonDialogs()));
  connect(saveSPCOnNextNote, SIGNAL(pressed()), this, SLOT(setSaveSPCOnNextNote()));
  connect(saveSPCImmediately, SIGNAL(pressed()), this, SLOT(setSaveSPCImmediately()));
}

void AdvancedSettingsWindow::initializeUi() {
  lstring part;

  part.split(";", video.driver_list());
  for(unsigned i = 0; i < part.size(); i++) {
    videoDriver->addItem(part[i]);
    if(part[i] == config().system.video) videoDriver->setCurrentIndex(i);
  }

  part.split(";", audio.driver_list());
  for(unsigned i = 0; i < part.size(); i++) {
    audioDriver->addItem(part[i]);
    if(part[i] == config().system.audio) audioDriver->setCurrentIndex(i);
  }

  part.split(";", input.driver_list());
  for(unsigned i = 0; i < part.size(); i++) {
    inputDriver->addItem(part[i]);
    if(part[i] == config().system.input) inputDriver->setCurrentIndex(i);
  }

  regionAuto->setChecked(SNES::config().region == SNES::System::Region::Autodetect);
  regionNTSC->setChecked(SNES::config().region == SNES::System::Region::NTSC);
  regionPAL->setChecked (SNES::config().region == SNES::System::Region::PAL);

  portSatellaview->setChecked(SNES::config().expansion_port == SNES::System::ExpansionPortDevice::BSX);
  portNone->setChecked       (SNES::config().expansion_port == SNES::System::ExpansionPortDevice::None);

  if (SNES::PPU::SupportsVRAMExpansion) {
    vram64kb->setChecked(SNES::config().vram_size == 0);
    vram128kb->setChecked(SNES::config().vram_size == 1);
    vram256kb->setChecked(SNES::config().vram_size == 2);
    connect(vram64kb, SIGNAL(pressed()), this, SLOT(setVRAM64kb()));
    connect(vram128kb, SIGNAL(pressed()), this, SLOT(setVRAM128kb()));
    connect(vram256kb, SIGNAL(pressed()), this, SLOT(setVRAM256kb()));
  } else {
    vram64kb->setChecked(true);
    vram128kb->setEnabled(false);
    vram256kb->setEnabled(false);
  }
  focusPause->setChecked (config().input.focusPolicy == Configuration::Input::FocusPolicyPauseEmulation);
  focusIgnore->setChecked(config().input.focusPolicy == Configuration::Input::FocusPolicyIgnoreInput);
  focusAllow->setChecked (config().input.focusPolicy == Configuration::Input::FocusPolicyAllowInput);

  autoSaveEnable->setChecked(config().system.autoSaveMemory);
  rewindEnable->setChecked(config().system.rewindEnabled);
  allowInvalidInput->setChecked(config().input.allowInvalidInput);
  useCommonDialogs->setChecked(config().diskBrowser.useCommonDialogs);
  
  saveSPCOnNextNote->setChecked (SNES::config().spc_save_policy == SNES::SMP::SPCSavePolicy::OnNextNote);
  saveSPCImmediately->setChecked(SNES::config().spc_save_policy == SNES::SMP::SPCSavePolicy::Immediately);
}

void AdvancedSettingsWindow::videoDriverChange(int index) {
  if(index >= 0) config().system.video = videoDriver->itemText(index).toUtf8().data();
}

void AdvancedSettingsWindow::audioDriverChange(int index) {
  if(index >= 0) config().system.audio = audioDriver->itemText(index).toUtf8().data();
}

void AdvancedSettingsWindow::inputDriverChange(int index) {
  if(index >= 0) config().system.input = inputDriver->itemText(index).toUtf8().data();
}

void AdvancedSettingsWindow::setRegionAuto() { SNES::config().region = SNES::System::Region::Autodetect; }
void AdvancedSettingsWindow::setRegionNTSC() { SNES::config().region = SNES::System::Region::NTSC; }
void AdvancedSettingsWindow::setRegionPAL()  { SNES::config().region = SNES::System::Region::PAL; }

void AdvancedSettingsWindow::setPortSatellaview() { SNES::config().expansion_port = SNES::System::ExpansionPortDevice::BSX; }
void AdvancedSettingsWindow::setPortNone()        { SNES::config().expansion_port = SNES::System::ExpansionPortDevice::None; }

void AdvancedSettingsWindow::setVRAM64kb()  { SNES::config().vram_size = 0; }
void AdvancedSettingsWindow::setVRAM128kb() { SNES::config().vram_size = 1; }
void AdvancedSettingsWindow::setVRAM256kb() { SNES::config().vram_size = 2; }

void AdvancedSettingsWindow::pauseWithoutFocus()       { config().input.focusPolicy = Configuration::Input::FocusPolicyPauseEmulation; }
void AdvancedSettingsWindow::ignoreInputWithoutFocus() { config().input.focusPolicy = Configuration::Input::FocusPolicyIgnoreInput; }
void AdvancedSettingsWindow::allowInputWithoutFocus()  { config().input.focusPolicy = Configuration::Input::FocusPolicyAllowInput; }

void AdvancedSettingsWindow::toggleAutoSaveEnable() {
  config().system.autoSaveMemory = autoSaveEnable->isChecked();
}

void AdvancedSettingsWindow::toggleRewindEnable() {
  config().system.rewindEnabled = rewindEnable->isChecked();
  state.resetHistory();
}

void AdvancedSettingsWindow::toggleAllowInvalidInput() {
  config().input.allowInvalidInput = allowInvalidInput->isChecked();
}

void AdvancedSettingsWindow::toggleUseCommonDialogs() {
  config().diskBrowser.useCommonDialogs = useCommonDialogs->isChecked();
}

void AdvancedSettingsWindow::setSaveSPCOnNextNote()  { SNES::config().spc_save_policy = SNES::SMP::SPCSavePolicy::OnNextNote; }
void AdvancedSettingsWindow::setSaveSPCImmediately() { SNES::config().spc_save_policy = SNES::SMP::SPCSavePolicy::Immediately; }
