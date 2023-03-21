#ifndef TEXT_ROLLER_H
#define TEXT_ROLLER_H

#include <Arduino.h>
#include <LinkedList.h>
#include "charImage.h"
#include "constant.h"
#include "ascii.h"


class TextRoller {
  public:
    int redValue;
    int greenValue;
    int blueValue;
    int interval;
    int verticalOffset;
    int step;
    String message;
    bool isRandomColor;


    int totalMessageCols;
    int totalOffsetCols;  // totalOffsetCol  = totalMessageCols + totalMatrixCols

    LinkedList<CharImage *> charImagesList;

  public:
    TextRoller();

    void configTextRoller(String inStr);

    // all seter
    void setRedValue(int v);
    void setGreenValue(int v);
    void setBlueValue(int v);
    void setInterval(int v);
    void setVerticalOffset(int v);
    void setTotalMessageCols(int v);
    void setTotalOffsetCols(int v);
    void setStep(int v);

  // set message will call configTextRoller function to recalcualte all the paramters
    void setMessage(String str);


    // reset function free all the memory in the charImagesList,and set TotalOffsetCols, TotalOffsetCols tpo 0
    void reset();

    void print();


};


#endif