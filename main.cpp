#include <QtGui/QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QtQml>

#include <models/treemodel.h>
#include <models/treemanipulator.h>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Set style into app.
    QQuickStyle::setStyle("Material");

    // Import all items into QML engine.
    engine.addImportPath(":/");

    const QUrl url(u"qrc:/assetel/qml/Main.qml"_qs);

    auto treeModel = new TreeModel(&engine);
    auto treeManipulator = new TreeManipulator(*treeModel, &engine);

    // Init QML interface
    auto c = engine.rootContext();
    c->setContextProperty("treeManipulator", QVariant::fromValue(treeManipulator));

    // Expose the model to QML
    c->setContextProperty("treeModel", QVariant::fromValue(treeModel));

    //const QUrl url(u"qrc:/qml/Main.qml"_qs);  // Correct URL path for Main.qml
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
