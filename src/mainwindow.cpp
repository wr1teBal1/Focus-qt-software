#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSvgRenderer>
#include <QPainter>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QBuffer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupConnections();
    setFocusPolicy(Qt::StrongFocus);
    loadDirectionIndicator();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{
    connect(ui->flightEmergencyButton, &QPushButton::clicked, this, &MainWindow::handleEmergencyStop);
    connect(ui->walkEmergencyButton, &QPushButton::clicked, this, &MainWindow::handleEmergencyStop);
}

void MainWindow::loadDirectionIndicator()
{
    QSvgRenderer renderer(QString::fromUtf8(":/icons/direction-indicator.svg"));
    QPixmap pixmap(200, 200);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    renderer.render(&painter);
    ui->flightDirectionIndicator->setPixmap(pixmap);
    ui->walkDirectionIndicator->setPixmap(pixmap);
}

void MainWindow::updateDirectionIndicator()
{
    // 读取SVG文件内容
    QFile file(":/icons/direction-indicator.svg");
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }
    
    QByteArray svgData = file.readAll();
    file.close();
    
    // 使用QXmlStreamReader和QXmlStreamWriter处理SVG内容
    QBuffer buffer;
    buffer.setData(svgData);
    buffer.open(QIODevice::ReadOnly);
    
    QXmlStreamReader reader(&buffer);
    
    QByteArray modifiedSvgData;
    QBuffer outputBuffer(&modifiedSvgData);
    outputBuffer.open(QIODevice::WriteOnly);
    
    QXmlStreamWriter writer(&outputBuffer);
    writer.setAutoFormatting(true);
    
    // 根据按键状态确定要高亮的方向ID
    QString highlightId;
    if (keyUp && keyRight) {
        highlightId = "up-right";
    } else if (keyUp && keyLeft) {
        highlightId = "up-left";
    } else if (keyDown && keyRight) {
        highlightId = "down-right";
    } else if (keyDown && keyLeft) {
        highlightId = "down-left";
    } else if (keyUp) {
        highlightId = "up";
    } else if (keyDown) {
        highlightId = "down";
    } else if (keyLeft) {
        highlightId = "left";
    } else if (keyRight) {
        highlightId = "right";
    }
    
    // 处理XML内容
    while (!reader.atEnd()) {
        reader.readNext();
        
        if (reader.isStartDocument()) {
            writer.writeStartDocument();
        } else if (reader.isEndDocument()) {
            writer.writeEndDocument();
        } else if (reader.isStartElement()) {
            writer.writeStartElement(reader.name().toString());
            
            // 复制所有属性
            for (const QXmlStreamAttribute &attr : reader.attributes()) {
                // 如果是path元素且有id属性，检查是否需要高亮
                if (reader.name() == "path" && attr.name() == "id") {
                    QString id = attr.value().toString();
                    writer.writeAttribute(attr.name().toString(), attr.value().toString());
                    
                    // 设置填充颜色
                    if (!highlightId.isEmpty() && id == highlightId) {
                        writer.writeAttribute("fill", "#2196F3"); // 高亮颜色
                    } else {
                        writer.writeAttribute("fill", "#e0e0e0"); // 默认颜色
                    }
                    
                    // 跳过原始的fill属性
                    continue;
                }
                
                // 如果不是fill属性或者不是path元素，直接复制
                if (!(reader.name() == "path" && attr.name() == "fill")) {
                    writer.writeAttribute(attr.name().toString(), attr.value().toString());
                }
            }
        } else if (reader.isEndElement()) {
            writer.writeEndElement();
        } else if (reader.isCharacters()) {
            writer.writeCharacters(reader.text().toString());
        }
    }
    
    outputBuffer.close();
    
    // 使用修改后的SVG数据创建渲染器
    QSvgRenderer modifiedRenderer(modifiedSvgData);
    
    // 渲染到pixmap
    QPixmap pixmap(200, 200);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    modifiedRenderer.render(&painter);
    
    // 更新两个界面的图标
    ui->flightDirectionIndicator->setPixmap(pixmap);
    ui->walkDirectionIndicator->setPixmap(pixmap);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) return;

    switch (event->key()) {
        case Qt::Key_W: keyW = true; break;
        case Qt::Key_S: keyS = true; break;
        case Qt::Key_Up: keyUp = true; break;
        case Qt::Key_Down: keyDown = true; break;
        case Qt::Key_Left: keyLeft = true; break;
        case Qt::Key_Right: keyRight = true; break;
    }

    updateKeyStatus();
    updateDirectionIndicator();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) return;

    switch (event->key()) {
        case Qt::Key_W: keyW = false; break;
        case Qt::Key_S: keyS = false; break;
        case Qt::Key_Up: keyUp = false; break;
        case Qt::Key_Down: keyDown = false; break;
        case Qt::Key_Left: keyLeft = false; break;
        case Qt::Key_Right: keyRight = false; break;
    }

    updateKeyStatus();
    updateDirectionIndicator();
}

void MainWindow::updateKeyStatus()
{
    QString flightStatus = "按键状态:\nW/S: ";
    if (keyW) flightStatus += "上升";
    else if (keyS) flightStatus += "下降";
    else flightStatus += "停止";

    flightStatus += "\n方向: ";
    if (keyUp && keyRight) flightStatus += "右上";
    else if (keyUp && keyLeft) flightStatus += "左上";
    else if (keyDown && keyRight) flightStatus += "右下";
    else if (keyDown && keyLeft) flightStatus += "左下";
    else if (keyUp) flightStatus += "前进";
    else if (keyDown) flightStatus += "后退";
    else if (keyLeft) flightStatus += "左移";
    else if (keyRight) flightStatus += "右移";
    else flightStatus += "停止";

    QString walkStatus = "按键状态:\n方向: ";
    if (keyUp && keyRight) walkStatus += "右上";
    else if (keyUp && keyLeft) walkStatus += "左上";
    else if (keyDown && keyRight) walkStatus += "右下";
    else if (keyDown && keyLeft) walkStatus += "左下";
    else if (keyUp) walkStatus += "前进";
    else if (keyDown) walkStatus += "后退";
    else if (keyLeft) walkStatus += "左移";
    else if (keyRight) walkStatus += "右移";
    else walkStatus += "停止";

    ui->flightKeyStatusLabel->setText(flightStatus);
    ui->walkKeyStatusLabel->setText(walkStatus);
}

void MainWindow::handleEmergencyStop()
{
    keyW = keyS = keyUp = keyDown = keyLeft = keyRight = false;
    updateKeyStatus();
    updateDirectionIndicator();
}