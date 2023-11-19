class Background {
  struct ID { enum { BG1, BG2, BG3, BG4 }; };
  unsigned id;

  struct Mode { enum  { BPP2, BPP4, BPP8, Mode7, Inactive }; };
  struct ScreenSize { enum { Size32x32, Size32x64, Size64x32, Size64x64 }; };
  struct TileSize { enum { Size8x8, Size16x16 }; };
  struct Screen { enum { Main, Sub }; };

  struct Regs {
    unsigned tiledata_addr;
    unsigned screen_addr;
    unsigned screen_size;
    bool mosaic;
    bool tile_size;

    unsigned mode;
    unsigned priority0;
    unsigned priority1;

    bool main_enable;
    bool sub_enable;

    unsigned hoffset;
    unsigned voffset;
  } regs;

  struct Pixel {
    unsigned priority;
    uint8 palette;  //0 = none (transparent)
    uint16 tile;
  };
  
  struct Output {
    Pixel main, sub;
  } output;

  struct {
    signed x;
    signed y;

    unsigned mosaic_hcounter;
    unsigned mosaic_hoffset;
    Pixel mosaic;

    unsigned tile_counter;
    unsigned tile;
    unsigned priority;
    unsigned palette_number;
    unsigned palette_index;
    uint8 data[8];
  };

  void frame();
  void scanline();
  void run(bool screen);
  void reset();

  void get_tile();
  unsigned get_tile_color();
  unsigned get_tile(unsigned x, unsigned y);
  signed clip(signed n);
  void run_mode7();

  void serialize(serializer&);
  Background(PPU &self, unsigned id);

  PPU &self;
  friend class PPU;
  friend class PPUDebugger;
};
