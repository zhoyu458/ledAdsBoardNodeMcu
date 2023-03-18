
#define DATA_PIN D0
#define SINGLE_MATRIX_ROWS 16
#define SINGLE_MATRIX_COLS 16
#define NUMBER_OF_MATRIX 3
#define NUM_LEDS (SINGLE_MATRIX_ROWS * SINGLE_MATRIX_COLS * NUMBER_OF_MATRIX)

#define TOTAL_MATRIX_ROWS (SINGLE_MATRIX_ROWS * NUMBER_OF_MATRIX)

#define TOTAL_MATRIX_COLS (SINGLE_MATRIX_COLS * NUMBER_OF_MATRIX)

#define SINGLE_MATRIX_LEDS (SINGLE_MATRIX_ROWS * SINGLE_MATRIX_COLS)

#define ASCII_ROWS 6


#include <FastLED.h>
#include "ascii.h"



struct Position {
  int row;
  int col;
};

struct CharImage {
  int size;
  int cols;
  int offset;  // the offset of each image is depending on all images before the current one;
  bool* imagePtr;
};

// Define the array of leds
CRGB leds[NUM_LEDS];
int positionToNumber(int rowIndex, int colIndex);
void showChar(bool* charBinary, int size);

void ledsOff();
void test();

int RED_VALUE = 1;
int GREEN_VALUE = 1;
int BLUE_VALUE = 0;
int INTERVAL = 150;
int VERTICAL_OFFSET = 3;

void setup() {

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  Serial.begin(115200);

  FastLED.clear();

  delay(5000);
  Serial.println("Program start here");
}

void loop() {

  while(!Serial.available()){

    RED_VALUE = random(0, 20);
    GREEN_VALUE = random(0, 20);
    BLUE_VALUE = random(0, 20);

    showMessage("! chris maggie !");

  }

  INTERVAL = Serial.parseInt();


}

void showMessage(String str) {
  str.toLowerCase();
  int length = str.length();

  int totalMessageCols = 0;

  // declare an array of pointer, each pointer is pointing to an array
  CharImage* CharImageArray[length];

  for (int i = 0; i < length; i++) {
    CharImage* image = new CharImage();
    if (str.charAt(i) == 'a') {
      image->size = sizeof(A);
      image->imagePtr = A;

    } else if (str.charAt(i) == 'b') {
      image->size = sizeof(B);
      image->imagePtr = B;

    } else if (str.charAt(i) == 'c') {

      image->size = sizeof(C);
      image->imagePtr = C;
    } else if (str.charAt(i) == 'd') {
      image->size = sizeof(D);
      image->imagePtr = D;

    } else if (str.charAt(i) == 'e') {
      image->size = sizeof(E);
      image->imagePtr = E;
    } else if (str.charAt(i) == 'f') {
      image->size = sizeof(F);
      image->imagePtr = F;
    } else if (str.charAt(i) == 'g') {
      image->size = sizeof(G);
      image->imagePtr = G;
    } else if (str.charAt(i) == 'h') {
      image->size = sizeof(H);
      image->imagePtr = H;
    } else if (str.charAt(i) == 'i') {
      image->size = sizeof(I);
      image->imagePtr = I;
    } else if (str.charAt(i) == 'g') {
      image->size = sizeof(G);
      image->imagePtr = G;
    } else if (str.charAt(i) == 'k') {
      image->size = sizeof(K);
      image->imagePtr = K;
    } else if (str.charAt(i) == 'l') {
      image->size = sizeof(L);
      image->imagePtr = L;
    } else if (str.charAt(i) == 'm') {
      image->size = sizeof(M);
      image->imagePtr = M;
    } else if (str.charAt(i) == 'n') {
      image->size = sizeof(N);
      image->imagePtr = N;
    } else if (str.charAt(i) == 'o') {
      image->size = sizeof(O);
      image->imagePtr = O;
    } else if (str.charAt(i) == 'p') {
      image->size = sizeof(P);
      image->imagePtr = P;
    } else if (str.charAt(i) == 'q') {
      image->size = sizeof(Q);
      image->imagePtr = Q;
    } else if (str.charAt(i) == 'r') {
      image->size = sizeof(R);
      image->imagePtr = R;
    } else if (str.charAt(i) == 's') {
      image->size = sizeof(S);
      image->imagePtr = S;
    } else if (str.charAt(i) == 't') {
      image->size = sizeof(T);
      image->imagePtr = T;
    }else if (str.charAt(i) == 'u') {
      image->size = sizeof(U);
      image->imagePtr = U;
    }else if (str.charAt(i) == 'v') {
      image->size = sizeof(V);
      image->imagePtr = V;
    }else if (str.charAt(i) == 'w') {
      image->size = sizeof(W);
      image->imagePtr = W;
    }else if (str.charAt(i) == 'x') {
      image->size = sizeof(X);
      image->imagePtr = X;
    }else if (str.charAt(i) == 'y') {
      image->size = sizeof(Y);
      image->imagePtr = Y;
    }else if (str.charAt(i) == 'z') {
      image->size = sizeof(Z);
      image->imagePtr = Z;
    }else if (str.charAt(i) == ' ') {
      image->size = sizeof(SPACE);
      image->imagePtr = SPACE;
    }else if (str.charAt(i) == '!') {
      image->size = sizeof(HEART);
      image->imagePtr = HEART;
    }

    image->cols = (image->size) / ASCII_ROWS;

    totalMessageCols = totalMessageCols + image->cols;
    // add the image to the array
    CharImageArray[i] = image;
  }

  // The for loop is below is to work out all the offset of each image
  // the first image (index 0 )offset is 0, start from index 1
  for (int i = 1; i < length; i++) {
    CharImage* cur = CharImageArray[i];
    CharImage* pre = CharImageArray[i - 1];

    cur->offset = pre->offset + pre->cols;
  }


  // render the image

  for (int step = 0; step < totalMessageCols + (SINGLE_MATRIX_COLS * NUMBER_OF_MATRIX); step++) {
    for (int i = 0; i < length; i++) {  // looping each image
      CharImage* image = CharImageArray[i];
      for (int j = 0; j < image->size; j++) {
        if (image->imagePtr[j] == true) continue;

        Position pos = indexToPosition(image->size, j);

        int newRow = pos.row + VERTICAL_OFFSET;
        int newCol = pos.col + SINGLE_MATRIX_COLS * NUMBER_OF_MATRIX + (image->offset) - step;

        if (newRow < 0 || newRow >= TOTAL_MATRIX_ROWS) continue;
        if (newCol < 0 || newCol >= TOTAL_MATRIX_COLS) continue;

        int ledNum = positionToNumber(newRow, newCol);
        leds[ledNum] = CRGB(RED_VALUE, GREEN_VALUE, BLUE_VALUE);
      }
    }
    FastLED.show();
    delay(INTERVAL);
    FastLED.clear();

    if(Serial.available()) return;
  }




  // release all pointer to free memory

  for (int i = 0; i < length; i++) {
    CharImage* ptr = CharImageArray[i];

    delete ptr;
    ptr = NULL;
  }
}







int positionToNumber(int rowIndex, int colIndex) {
  int matrixBlockOffset = colIndex / SINGLE_MATRIX_COLS;
  rowIndex = rowIndex % SINGLE_MATRIX_ROWS;
  colIndex = colIndex % SINGLE_MATRIX_COLS;
  int ledNum = 0;

  if (rowIndex % 2 == 0) {
    ledNum = (SINGLE_MATRIX_ROWS - rowIndex - 1) * SINGLE_MATRIX_ROWS + (SINGLE_MATRIX_COLS - colIndex - 1);
    ledNum += matrixBlockOffset * SINGLE_MATRIX_LEDS;
  } else {
    ledNum = (SINGLE_MATRIX_ROWS - rowIndex - 1) * SINGLE_MATRIX_ROWS + colIndex;
    ledNum += matrixBlockOffset * SINGLE_MATRIX_LEDS;
  }

  return ledNum;
}


// function convert one dimension char array index to a 2 dimension position
Position indexToPosition(int arraySize, int index) {

  int cols = arraySize / ASCII_ROWS;


  int r = index / cols;
  int c = index % cols;

  Position pos;
  pos.row = r;
  pos.col = c;

  return pos;
}

int calcLedNumFromCharBinaryIndex(int binaryCharArraySize, int index) {

  Position pos = indexToPosition(binaryCharArraySize, index);

  return positionToNumber(pos.row, pos.col);
}

void showChar(bool* charBinary, int size) {
  int ledNum = 0;

  for (int i = 0; i < size; i++) {
    if (charBinary[i] == false) {
      ledNum = calcLedNumFromCharBinaryIndex(size, i);
      leds[ledNum] = CRGB(random(0, 10), random(0, 10), random(0, 10));
    }
  }
  FastLED.show();

  delay(1000);

  FastLED.clear();
  FastLED.show();

  delay(1000);
}

void ledsOff() {
  for (int i = 0; i < 256; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}
