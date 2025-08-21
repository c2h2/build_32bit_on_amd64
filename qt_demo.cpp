#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSlider>
#include <QtCore/QTimer>
#include <QtCore/QDebug>

class ArchitectureDemo : public QWidget
{
    Q_OBJECT

public:
    ArchitectureDemo(QWidget *parent = nullptr) : QWidget(parent)
    {
        setupUI();
        updateArchInfo();
        
        // Timer to update progress bar
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &ArchitectureDemo::updateProgress);
        timer->start(100);
    }

private slots:
    void updateProgress()
    {
        static int progress = 0;
        progress = (progress + 1) % 101;
        progressBar->setValue(progress);
    }
    
    void onButtonClicked()
    {
        QString text = lineEdit->text();
        if (!text.isEmpty()) {
            textEdit->append("Input: " + text);
            lineEdit->clear();
        }
    }
    
    void onSliderChanged(int value)
    {
        sliderLabel->setText(QString("Slider Value: %1").arg(value));
    }

private:
    void setupUI()
    {
        setWindowTitle("Qt5 Cross-compilation Demo");
        setFixedSize(400, 500);
        
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        
        // Architecture info
        archLabel = new QLabel(this);
        archLabel->setStyleSheet("font-weight: bold; color: blue;");
        mainLayout->addWidget(archLabel);
        
        // Size info
        sizeLabel = new QLabel(this);
        sizeLabel->setWordWrap(true);
        mainLayout->addWidget(sizeLabel);
        
        // Input section
        QHBoxLayout *inputLayout = new QHBoxLayout();
        lineEdit = new QLineEdit(this);
        lineEdit->setPlaceholderText("Enter some text...");
        QPushButton *button = new QPushButton("Add Text", this);
        connect(button, &QPushButton::clicked, this, &ArchitectureDemo::onButtonClicked);
        
        inputLayout->addWidget(lineEdit);
        inputLayout->addWidget(button);
        mainLayout->addLayout(inputLayout);
        
        // Text display
        textEdit = new QTextEdit(this);
        textEdit->setMaximumHeight(150);
        textEdit->append("Qt5 Demo Application Started");
        textEdit->append("This demonstrates cross-compilation capabilities");
        mainLayout->addWidget(textEdit);
        
        // Progress bar
        QLabel *progressLabel = new QLabel("Progress Demo:", this);
        progressBar = new QProgressBar(this);
        progressBar->setRange(0, 100);
        mainLayout->addWidget(progressLabel);
        mainLayout->addWidget(progressBar);
        
        // Slider
        QLabel *sliderTitle = new QLabel("Slider Demo:", this);
        QSlider *slider = new QSlider(Qt::Horizontal, this);
        slider->setRange(0, 100);
        slider->setValue(50);
        sliderLabel = new QLabel("Slider Value: 50", this);
        
        connect(slider, &QSlider::valueChanged, this, &ArchitectureDemo::onSliderChanged);
        
        mainLayout->addWidget(sliderTitle);
        mainLayout->addWidget(slider);
        mainLayout->addWidget(sliderLabel);
        
        mainLayout->addStretch();
    }
    
    void updateArchInfo()
    {
        QString arch;
        QString platform;
        
#if defined(__x86_64__) || defined(_M_X64)
        arch = "x86_64 (64-bit)";
#elif defined(__i386) || defined(_M_IX86)
        arch = "i386 (32-bit)";
#else
        arch = "Unknown architecture";
#endif

#ifdef Q_OS_LINUX
        platform = "Linux";
#elif defined(Q_OS_WIN)
        platform = "Windows";
#elif defined(Q_OS_MAC)
        platform = "macOS";
#else
        platform = "Unknown OS";
#endif

        archLabel->setText(QString("Architecture: %1 on %2").arg(arch, platform));
        
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
        
        sizeLabel->setText(sizeInfo);
    }

private:
    QLabel *archLabel;
    QLabel *sizeLabel;
    QLabel *sliderLabel;
    QLineEdit *lineEdit;
    QTextEdit *textEdit;
    QProgressBar *progressBar;
    QTimer *timer;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    ArchitectureDemo window;
    window.show();
    
    return app.exec();
}

#include "qt_demo.moc"