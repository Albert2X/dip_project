/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef MDICHILD_H
#define MDICHILD_H

#include <QGraphicsView>
#include <QGraphicsItem>

//用于撤销功能，详见mainwindow.cpp
#define loopMax 10
class Loop
{
public:

    void in(QImage val)
    {

        if(!emptyFlag ||  head == tail)   //满环判断
        {
            tail = head+1;

            if(tail>loopMax-1)  //循环处理
                tail = 0;
        }
        emptyFlag = 0;
        IMG[head]=val;

        //为下一轮读入数据做准备
        head++;
        if(head>loopMax-1)   //循环处理
            head = 0;


    }

    QImage out()
    {
        if(emptyFlag)   //空环判断
        {

            //应该配合 isEmpty  在运用它时避免在环为空的时候执行out操作
            return IMG[head];  //这里随便return了一个值，结合上面的说明，实际上不会出现这种情况的返回值
        }

        head--;
        if(head<0)  //循环处理
            head = loopMax-1;

        if(head==tail)   //空环 提前将emptyFlag置1
            emptyFlag = 1;

        return IMG[head];

    }

    bool isEmpty()
    {
        return emptyFlag;
    }

private:
    int head=0;
    int tail=0;
    bool emptyFlag =1;
    QImage IMG[loopMax];
};



class MdiChild : public QGraphicsView
{
    Q_OBJECT

public:
    MdiChild();
    MdiChild(QObject *owner);

    void newFile();
    bool loadFromFile(const QString &fileName);
    bool loadFromImage(const QImage &image);
    bool copy();
    bool paste();
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
    QString userFriendlyCurrentFile();
    QString currentFile() { return curFile; }
    void setCurrentFile(const QString &fileName);
    void setLabel(const QString &str);
    void setImage(QImage newImage);

    Loop loopstack;  //用于撤销功能

    QObject *owner;
    QGraphicsScene scene;
    QGraphicsPixmapItem imageItem;
    QImage image;
    QString label;


protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void imageWasModified();
signals:
    void imageChanged();
    void ownerClosed();

private:


    bool maybeSave();
    QString strippedName(const QString &fullFileName);

    QString curFile;
    bool isUntitled;
    bool isModified;
};

#endif
