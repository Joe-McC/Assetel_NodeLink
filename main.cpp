#include <QtQml>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
//#include <QQuickStyle>

/*#include <misc/utilities.h>
#include <misc/mydocument.h>
#include <misc/treemodel.h>
#include <misc/treemanipulator.h>
#include <misc/parentsmodel.h>
#include <misc/nodelistmodel.h>
#include <misc/xmlconnector.h>
#include <misc/connectorlistmodel.h>
*/
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Set style into app.
    //QQuickStyle::setStyle("Material");

    //Import all items into QML engine.
    //engine.addImportPath(":/");

    //engine.addImportPath(":/");
    engine.addImportPath("qrc:/modules");




    //const QUrl url(u"qrc:/main.qml"_qs);


    //:/main.   qml\ui\resources

    //const QUrl url(u"qrc:/main.qml"_qs);

    const QUrl url(QStringLiteral("qrc:/resources/main.qml"));

    const QUrl

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
    /*
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    engine.addImportPath("qrc:/modules");

    auto utilities = &Misc::Utilities::getInstance();
    //auto myDocument = &Misc::MyDocument::getInstance();

// create XMLProcessor instance here and pass to mydocument and nodemodellist? OR add connections between myDocument and NodeListModel
    //auto xmlProcessor = &Misc::XMLProcessor::getInstance();

    auto myDocument = new Misc::MyDocument(engine);
    auto nodeListModel = new Misc::NodeListModel(&engine, myDocument);
    auto connectorListModel = new Misc::ConnectorListModel(&engine, myDocument);

    auto treeModel = new TreeModel(&engine, myDocument);
    auto treeManipulator = new TreeManipulator(*treeModel, &engine);

    Misc::ParentsModel parentsModel;

    // Configure dark UI
    Misc::Utilities::configureDarkUi();

    // Init QML interface
    auto c = engine.rootContext();
    QQuickStyle::setStyle("Fusion");
    c->setContextProperty("Cpp_Misc_Utilities", utilities);
    c->setContextProperty("Cpp_Misc_My_Document", myDocument);
    c->setContextProperty("treeManipulator", QVariant::fromValue(treeManipulator));
    c->setContextProperty("availableParentsModel", &parentsModel);
    c->setContextProperty("nodeListModel", nodeListModel);
    c->setContextProperty("connectorListModel", connectorListModel);

    qmlRegisterType<Misc::XMLConnector>("Misc", 1, 0, "XMLConnector");


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
*/
}
