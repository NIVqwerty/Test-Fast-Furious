//========================================================================
//! @file       Main.cpp
//{=======================================================================
//!
//! @brief      <Заголовок>\n
//! @brief      <Подзаголовок>
//!
//! @version    [Version 0.01 alpha, build 1]
//! @author     Copyright (C) <Автор>, <Год> (<Имя> <Почта>)
//! @date       <Дата>
//!
//! @par        Протестировано
//!           - (TODO: список платформ)
//!
//! @todo     - (TODO: список ближайших планов по этому файлу)
//!
//! @bug      - (TODO: список найденных ошибок в этом файле)
//!
//! @par        История изменений файла
//!           - Версия 0.01 Alpha
//!             - Только что созданный файл
//!
//}=======================================================================

#include "TXLib.h"
#include <fstream>

using namespace std;

struct Forma
{
   string text_question;
   HDC pic_answer1;
   HDC pic_answer2;
   HDC pic_answer3;
   string text_answer1;
   string text_answer2;
   string text_answer3;
   int correct;

   void draw()
   {
        txSetColor (TX_LIGHTGREEN);
        txSelectFont ("Times", 40);
        txDrawText (20, 100, 780, 150, text_question.c_str());
        txSelectFont ("Times", 30);
        txDrawText (20, 500, 250, 550, text_answer1.c_str());
        txDrawText (285, 500, 515, 550, text_answer2.c_str());
        txDrawText (550, 500, 780, 550, text_answer3.c_str());
        txBitBlt(txDC(), 20, 220, 230, 170, pic_answer1);
        txBitBlt(txDC(), 285, 220, 230, 170, pic_answer2);
        txBitBlt(txDC(), 550, 220, 230, 170, pic_answer3);
   }
};

bool click(int x)
{
    return(txMouseButtons() == 1 && txMouseX()>x &&
            txMouseX()<x+230 && txMouseY()>500 && txMouseY()<550);
}

void drawOblast()
{
    txRectangle (550, 20, 750, 70);    //область № вопроса
    txRectangle (20, 100, 780, 150);   //область текст вопроса
    txRectangle (20, 220, 250, 390);   //область картинка ответа 1
    txRectangle (20, 500, 250, 550);   //область текст ответа 1
    txRectangle (285, 220, 515, 390);   //область картинка ответа 2
    txRectangle (285, 500, 515, 550);   //область текст ответа 2
    txRectangle (550, 220, 780, 390);   //область картинка ответа 3
    txRectangle (550, 500, 780, 550);   //область текст ответа 3
}


string getParts(int *pos2, string str)
{
    int pos1 = *pos2+1;
    *pos2 = str.find(",", pos1);
    string part = str.substr(pos1, *pos2-pos1);
    return part;
}

int main()
{
txCreateWindow (800, 600);
txTextCursor (false);
setlocale(LC_ALL, "Russian");



    Forma form;
    Forma form_list[20];

    string stroka;
    int i = 0;
    ifstream file("test.txt");

    while(file.good())
    {
        getline(file, stroka);
        int pos2 = -1;
        form_list[i].text_question = getParts(&pos2, stroka);
        form_list[i].pic_answer1 = txLoadImage(getParts(&pos2, stroka).c_str());
        form_list[i].pic_answer2 = txLoadImage(getParts(&pos2, stroka).c_str());
        form_list[i].pic_answer3 = txLoadImage(getParts(&pos2, stroka).c_str());
        form_list[i].text_answer1 = getParts(&pos2, stroka);
        form_list[i].text_answer2 = getParts(&pos2, stroka);
        form_list[i].text_answer3 = getParts(&pos2, stroka);
        form_list[i].correct = atoi(getParts(&pos2, stroka).c_str());
        i++;
    }
    file.close();

    int count_question = i;
    int n_question = 1;
    int score = 0;
    char str[25];


    while(n_question <= count_question)
    {
        txSetFillColor (TX_BLACK);
        txClear();
        txBegin();

        txSetColor (TX_WHITE);
        txSetFillColor (TX_TRANSPARENT);

        drawOblast();

        sprintf(str, "Вопрос №%d из %d", n_question, count_question);
        txDrawText(550, 20, 750, 70, str);

        form = form_list[n_question-1];

        form.draw();

        if(click(20))
        {
            if(form.correct == 1) score++;
            while(txMouseButtons() == 1) txSleep(50);
            n_question++;
        }

        if(click(285))
        {
            if(form.correct == 2) score++;
            while(txMouseButtons() == 1) txSleep(50);
            n_question++;
        }

        if(click(550))
        {
            if(form.correct == 3) score++;
            while(txMouseButtons() == 1) txSleep(50);
            n_question++;
        }

        txEnd();
        txSleep(50);
    }

txSetFillColor (TX_BLACK);
txClear();
sprintf(str, "Ваш результат - %d из %d", score, count_question);
txDrawText(0, 0, 800, 600, str);


return 0;
}
