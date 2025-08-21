#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    QWidget window;
    window.setWindowTitle("Qt5 Cross-compilation Demo");
    window.setFixedSize(350, 200);
    
    QVBoxLayout *layout = new QVBoxLayout(&window);
    
    // Architecture info
    QString arch;
#if defined(__x86_64__) || defined(_M_X64)
    arch = "x86_64 (64-bit)";
#elif defined(__i386) || defined(_M_IX86)
    arch = "i386 (32-bit)";
#else
    arch = "Unknown architecture";
#endif

    QLabel *archLabel = new QLabel(QString("Architecture: %1").arg(arch));
    archLabel->setStyleSheet("font-weight: bold; color: blue; font-size: 14px;");
    layout->addWidget(archLabel);
    
    // Size info
    QString sizeInfo = QString(
        "Data Type Sizes:\n"
        "sizeof(int): %1 bytes\n"
        "sizeof(long): %2 bytes\n"
        "sizeof(void*): %3 bytes\n"
        "sizeof(size_t): %4 bytes"
    ).arg(sizeof(int))
     .arg(sizeof(long))
     .arg(sizeof(void*))
     .arg(sizeof(size_t));
    
    QLabel *sizeLabel = new QLabel(sizeInfo);
    sizeLabel->setWordWrap(true);
    layout->addWidget(sizeLabel);
    
    // Button
    QPushButton *button = new QPushButton("Show Qt Version");
    layout->addWidget(button);
    
    // Connect button - using lambda to avoid MOC
    QObject::connect(button, &QPushButton::clicked, [&]() {
        QMessageBox::information(&window, "Qt Version", 
            QString("Qt Version: %1\nCompiled for: %2").arg(qVersion(), arch));
    });
    
    layout->addStretch();
    
    window.show();
    
    return app.exec();
}