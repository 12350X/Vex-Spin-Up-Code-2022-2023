<<<<<<< HEAD

    typedef struct {
      int x;
      int y;
      int w;
      int h;
    }
      square;
            
    typedef struct {
      int x;
      int y;
    }
    point;
  class button
  {
    public: 
      square s;
      bool isDisabled;
      void (*functionpointer)(void);
      int CheckCollisions();
      typedef char *string;
      void setButtonDisabled(bool x);
      void clear();
      void setup(int x, int y, int width, int height, string text, void (*ptr)(void));
      void setup(square s, string text, void (*ptr)(void));
      void destroy();
  };
=======

    typedef struct {
      int x;
      int y;
      int w;
      int h;
    }
      square;
            
    typedef struct {
      int x;
      int y;
    }
    point;
  class button
  {
    public: 
      square s;
      bool isDisabled;
      void (*functionpointer)(void);
      int CheckCollisions();
      typedef char *string;
      void setButtonDisabled(bool x);
      void clear();
      void setup(int x, int y, int width, int height, string text, void (*ptr)(void));
      void setup(square s, string text, void (*ptr)(void));
      void destroy();
  };
>>>>>>> 779145db1c57a107f97e9b8889b5af11f9c0360d
