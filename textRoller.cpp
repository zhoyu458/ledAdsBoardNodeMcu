#include "textRoller.h"


#define DEFAULT_INTERVAL 100
#define DEFAULT_VERTICAL_OFFSET 4
#define DEFAULT_RED_VALUE 10
#define DEFAULT_GREEN_VALUE 10
#define DEFAULT_BLUE_VALUE 0
#define DEFAULT_BRIGHTNESS_FACTOR 2

TextRoller::TextRoller() {
  this->setRedValue(DEFAULT_RED_VALUE);
  this->setGreenValue(DEFAULT_GREEN_VALUE);
  this->setBlueValue(DEFAULT_BLUE_VALUE);
  this->setVerticalOffset(DEFAULT_VERTICAL_OFFSET);
  this->setInterval(DEFAULT_INTERVAL);
  this->setMessage("welcome");
  this->isRandomColor = false;
  this->brightnessFactor = DEFAULT_BRIGHTNESS_FACTOR;
}

void TextRoller::setRedValue(int v) {
  this->redValue = v ;
}

void TextRoller::setGreenValue(int v) {
  this->greenValue = v ;
}

void TextRoller::setBlueValue(int v) {
  this->blueValue = v ;
}

void TextRoller::setInterval(int v) {
  this->interval = v;
}

void TextRoller::setVerticalOffset(int v) {
  this->verticalOffset = v;
}

void TextRoller::setMessage(String str) {

  // if the incoming text is the same as the existing one , no need to configure again
  if (str.equals(this->message)) return;

  // clear up the previous configuration
  this->reset();


  str.toLowerCase();
  int length = str.length();

  this->message = str;

  //declare an array of pointer, each pointer is pointing to an array
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
    } else if (str.charAt(i) == 'u') {
      image->size = sizeof(U);
      image->imagePtr = U;
    } else if (str.charAt(i) == 'v') {
      image->size = sizeof(V);
      image->imagePtr = V;
    } else if (str.charAt(i) == 'w') {
      image->size = sizeof(W);
      image->imagePtr = W;
    } else if (str.charAt(i) == 'x') {
      image->size = sizeof(X);
      image->imagePtr = X;
    } else if (str.charAt(i) == 'y') {
      image->size = sizeof(Y);
      image->imagePtr = Y;
    } else if (str.charAt(i) == 'z') {
      image->size = sizeof(Z);
      image->imagePtr = Z;
    } else if (str.charAt(i) == ' ') {
      image->size = sizeof(SPACE);
      image->imagePtr = SPACE;
    } else if (str.charAt(i) == '!') {
      image->size = sizeof(HEART);
      image->imagePtr = HEART;
    } else if (str.charAt(i) == '0') {
      image->size = sizeof(ZERO);
      image->imagePtr = ZERO;
    } else if (str.charAt(i) == '1') {
      image->size = sizeof(ONE);
      image->imagePtr = ONE;
    } else if (str.charAt(i) == '2') {
      image->size = sizeof(TWO);
      image->imagePtr = TWO;
    } else if (str.charAt(i) == '3') {
      image->size = sizeof(THREE);
      image->imagePtr = THREE;
    } else if (str.charAt(i) == '4') {
      image->size = sizeof(FOUR);
      image->imagePtr = FOUR;
    } else if (str.charAt(i) == '5') {
      image->size = sizeof(FIVE);
      image->imagePtr = FIVE;
    } else if (str.charAt(i) == '6') {
      image->size = sizeof(SIX);
      image->imagePtr = SIX;
    } else if (str.charAt(i) == '7') {
      image->size = sizeof(SEVEN);
      image->imagePtr = SEVEN;
    } else if (str.charAt(i) == '8') {
      image->size = sizeof(EIGHT);
      image->imagePtr = EIGHT;
    } else if (str.charAt(i) == '9') {
      image->size = sizeof(NINE);
      image->imagePtr = NINE;
    } else if (str.charAt(i) == ':') {
      image->size = sizeof(COLON);
      image->imagePtr = COLON;
    }

    image->cols = (image->size) / ASCII_ROWS;

    this->totalMessageCols += image->cols;
    // add the image to the linkedList

    this->charImagesList.add(this->charImagesList.size(), image);
  }

  this->totalOffsetCols = this->totalMessageCols + (SINGLE_MATRIX_COLS * NUMBER_OF_MATRIX);


  for (int i = 1; i < this->charImagesList.size(); i++) {
    CharImage* cur = this->charImagesList.get(i);
    CharImage* pre = this->charImagesList.get(i - 1);

    cur->offset = pre->offset + pre->cols;
  }
}

void TextRoller::setBrightnessFactor(int v) {
  if (v < 0 || v > 10) {
    this->brightnessFactor = DEFAULT_BRIGHTNESS_FACTOR;
  } else {
    this->brightnessFactor = v;
  }
}

void TextRoller::setTotalMessageCols(int v) {
  this->totalMessageCols = v;
}

void TextRoller::setTotalOffsetCols(int v) {
  this->totalOffsetCols = v;
}

void TextRoller::setStep(int v) {
  this->step = v;
}

void TextRoller::configTextRoller(String str) {



  // if the incoming text is the same as the existing one , no need to configure again
  if (str.equals(this->message)) return;

  // clear up the previous configuration
  this->reset();


  str.toLowerCase();
  int length = str.length();

  this->message = str;

  Serial.println(str);

  //declare an array of pointer, each pointer is pointing to an array
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
    } else if (str.charAt(i) == 'u') {
      image->size = sizeof(U);
      image->imagePtr = U;
    } else if (str.charAt(i) == 'v') {
      image->size = sizeof(V);
      image->imagePtr = V;
    } else if (str.charAt(i) == 'w') {
      image->size = sizeof(W);
      image->imagePtr = W;
    } else if (str.charAt(i) == 'x') {
      image->size = sizeof(X);
      image->imagePtr = X;
    } else if (str.charAt(i) == 'y') {
      image->size = sizeof(Y);
      image->imagePtr = Y;
    } else if (str.charAt(i) == 'z') {
      image->size = sizeof(Z);
      image->imagePtr = Z;
    } else if (str.charAt(i) == ' ') {
      image->size = sizeof(SPACE);
      image->imagePtr = SPACE;
    } else if (str.charAt(i) == '!') {
      image->size = sizeof(HEART);
      image->imagePtr = HEART;
    } else if (str.charAt(i) == '0') {
      image->size = sizeof(ZERO);
      image->imagePtr = ZERO;
    } else if (str.charAt(i) == '1') {
      image->size = sizeof(ONE);
      image->imagePtr = ONE;
    } else if (str.charAt(i) == '2') {
      image->size = sizeof(TWO);
      image->imagePtr = TWO;
    } else if (str.charAt(i) == '3') {
      image->size = sizeof(THREE);
      image->imagePtr = THREE;
    } else if (str.charAt(i) == '4') {
      image->size = sizeof(FOUR);
      image->imagePtr = FOUR;
    } else if (str.charAt(i) == '5') {
      image->size = sizeof(FIVE);
      image->imagePtr = FIVE;
    } else if (str.charAt(i) == '6') {
      image->size = sizeof(SIX);
      image->imagePtr = SIX;
    } else if (str.charAt(i) == '7') {
      image->size = sizeof(SEVEN);
      image->imagePtr = SEVEN;
    } else if (str.charAt(i) == '8') {
      image->size = sizeof(EIGHT);
      image->imagePtr = EIGHT;
    } else if (str.charAt(i) == '9') {
      image->size = sizeof(NINE);
      image->imagePtr = NINE;
    } else if (str.charAt(i) == ':') {
      image->size = sizeof(COLON);
      image->imagePtr = COLON;
    }
    image->cols = (image->size) / ASCII_ROWS;

    this->totalMessageCols += image->cols;
    // add the image to the linkedList

    this->charImagesList.add(this->charImagesList.size(), image);
  }

  this->totalOffsetCols = this->totalMessageCols + (SINGLE_MATRIX_COLS * NUMBER_OF_MATRIX);


  for (int i = 1; i < this->charImagesList.size(); i++) {
    CharImage* cur = this->charImagesList.get(i);
    CharImage* pre = this->charImagesList.get(i - 1);

    cur->offset = pre->offset + pre->cols;
  }
}

void TextRoller::reset() {

  this->setTotalMessageCols(0);
  this->setTotalOffsetCols(0);


  for (int i = 0; i < this->charImagesList.size(); i++) {
    CharImage* ptr = this->charImagesList.get(i);

    delete ptr;
    ptr = NULL;
  }
  this->charImagesList.clear();
}


void TextRoller::print() {
  Serial.println("------------------------------------------");
  Serial.print("red: ");
  Serial.println(this->redValue);
  Serial.print("green: ");
  Serial.println(this->greenValue);
  Serial.print("blue: ");
  Serial.println(this->blueValue);


  Serial.print("verticalOffset: ");
  Serial.println(this->verticalOffset);

  Serial.print("interval: ");
  Serial.println(this->interval);

  Serial.print("message: ");
  Serial.println(this->message);


  Serial.print("TotalMessageCols: ");
  Serial.println(this->totalMessageCols);

  Serial.print("setTotalOffsetCols: ");
  Serial.println(this->totalOffsetCols);

  Serial.print("step: ");
  Serial.println(this->step);
}
