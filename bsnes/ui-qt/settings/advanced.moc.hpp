class AdvancedSettingsWindow : public QWidget {
  Q_OBJECT

public:
  QVBoxLayout *layout;

  QGridLayout *driverLayout;
  QLabel *videoLabel;
  QLabel *audioLabel;
  QLabel *inputLabel;
  QComboBox *videoDriver;
  QComboBox *audioDriver;
  QComboBox *inputDriver;
  QLabel *driverInfo;

  QLabel *regionTitle;
  QHBoxLayout *regionLayout;
  QButtonGroup *regionGroup;
  QRadioButton *regionAuto;
  QRadioButton *regionNTSC;
  QRadioButton *regionPAL;

  QLabel *portTitle;
  QHBoxLayout *portLayout;
  QButtonGroup *portGroup;
  QRadioButton *portSatellaview;
  QRadioButton *portNone;

  QLabel *vramTitle;
  QHBoxLayout *vramLayout;
  QButtonGroup *vramGroup;
  QRadioButton *vram64kb;
  QRadioButton *vram128kb;
  QRadioButton *vram256kb;

  QLabel *focusTitle;
  QHBoxLayout *focusLayout;
  QButtonGroup *focusButtonGroup;
  QRadioButton *focusPause;
  QRadioButton *focusIgnore;
  QRadioButton *focusAllow;

  QLabel *miscTitle;
  QCheckBox *autoSaveEnable;
  QCheckBox *rewindEnable;
  QCheckBox *allowInvalidInput;
  QCheckBox *useCommonDialogs;
  
  QLabel *saveSPCTitle;
  QHBoxLayout *saveSPCLayout;
  QButtonGroup *saveSPCButtonGroup;
  QRadioButton *saveSPCOnNextNote;
  QRadioButton *saveSPCImmediately;

  void initializeUi();
  AdvancedSettingsWindow();

public slots:
  void videoDriverChange(int index);
  void audioDriverChange(int index);
  void inputDriverChange(int index);
  void setRegionAuto();
  void setRegionNTSC();
  void setRegionPAL();
  void setPortSatellaview();
  void setPortNone();
  void setVRAM64kb();
  void setVRAM128kb();
  void setVRAM256kb();
  void pauseWithoutFocus();
  void ignoreInputWithoutFocus();
  void allowInputWithoutFocus();
  void toggleAutoSaveEnable();
  void toggleRewindEnable();
  void toggleAllowInvalidInput();
  void toggleUseCommonDialogs();
  void setSaveSPCOnNextNote();
  void setSaveSPCImmediately();
};

extern AdvancedSettingsWindow *advancedSettingsWindow;
