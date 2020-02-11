#include "../../headers/objectManagement/objectstoragemanager.h"

ObjectStorageManager::ObjectStorageManager(const QByteArray storageName)
    : objectStorageDir((storageName))
{
    objectStorageDir = globalObjectStorageName + objectStorageDir;
    Initialize();                    // initialize list objects that storage dir contain
    QDir().mkpath(objectStorageDir); // create directory for objects storage
}

QByteArray ObjectStorageManager::getObjectStorageDir() const
{
    return objectStorageDir;
}

uint ObjectStorageManager::getQuantityObjectsInStorage() const
{
    return objectsList.size();
}

// add new object to storage. That is all object data will write into the file
// "objectName.object"
bool ObjectStorageManager::addNewObject(Object3d newObject)
{
    // Format file object:
    // objectName quantityVertex quantityLines quantityTriangles quantityQuads
    if (newObject.getQuantityVertex3d() == 0)
    {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "Object is empty can't add to storage";
        return false;
    }
    QFile newObjectFile(objectStorageDir + '/' + newObject.getName() + ".object");
    if (newObjectFile.exists())
        newObjectFile.setFileName(findUniqueFileName(objectStorageDir + '/' + newObject.getName()));

    if (newObjectFile.open(QIODevice::WriteOnly))
    {
        newObjectFile.write(newObject.getName() + ' ' + QByteArray::number(newObject.getQuantityVertex3d())
                            + ' ' + QByteArray::number(newObject.getQuantityLines3d()) + ' '
                            + QByteArray::number(newObject.getQuantityTriangles3d()) + ' '
                            + QByteArray::number(newObject.getQuantityFaces3d()));

        {
            // write all vertex to file
            // format:
            // x y z

            std::vector<primitives::Point3d> temp = newObject.getVertex3dData(); // get all vertex from object
            for (auto i : temp)
                newObjectFile.write('\n' + QByteArray::number(i.x) + ' ' + QByteArray::number(i.y) + ' '
                                    + QByteArray::number(i.z));
        }

        {
            // write all lines to file
            // format:
            // indexPoint1 indexPoint2
            std::vector<primitives::Line3d> temp = newObject.getLines3dData(); // get all vertex from object
            for (auto i : temp)
                newObjectFile.write('\n' + QByteArray::number(i.indexVertex1) + ' '
                                    + QByteArray::number(i.indexVertex2));
        }

        {
            // write all triangles to file
            // format:
            // indexPoint1 indexPoint2 indexPoint3
            std::vector<primitives::Triangle3d> temp =
                newObject.getTrianglesData(); // get all vertex from object
            for (auto i : temp)
                newObjectFile.write('\n' + QByteArray::number(i.indexVertex1) + ' '
                                    + QByteArray::number(i.indexVertex2) + ' '
                                    + QByteArray::number(i.indexVertex3));
        }

        {
            // write all faces to file
            // format:
            // indexPoint1 indexPoint2 indexPoint3 indexPoint4  (need to add normal)
            std::vector<primitives::Face3d> temp = newObject.getFaces3dData(); // get all vertex from object
            for (auto i : temp)
                newObjectFile.write(
                    '\n' + QByteArray::number(i.indexVertex1) + ' ' + QByteArray::number(i.indexVertex2) + ' '
                    + QByteArray::number(i.indexVertex3) + ' ' + QByteArray::number(i.indexVertex4));
        }

        newObjectFile.close();
        objectsList.push_back(newObject.getName()); // add object to list
        return true;
    }
    else
        qDebug() << "[Error] Cannot open the file " << newObject.getName();
    return false;
}

// remove files "objectName.object" from storage
void ObjectStorageManager::removeObject(QString objectName)
{
    QFile(objectStorageDir + '/' + objectName + ".object").remove();
}

// convert data type "objectName.object" to object with data: vertex, lines,
// triangles, etc..
Object3d ObjectStorageManager::getObjectFromListByName(QString objectName)
{
    objectName += ".object";
    QFile objectFile(objectStorageDir + '/' + objectName);
    if (!objectFile.exists())
    {
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "File non exist " << objectFile;
        return Object3d();
    }
    if (objectFile.open(QIODevice::ReadOnly))
    {
        Object3d objectResult;
        QByteArray currentLine;
        QList<QByteArray> tempValues; // list that will contain parsed data
        QList<QByteArray> values;     // list that will contain parsed data
        //        uint quantityVertex = 0, quantityLines = 0, quantityTriangles = 0,
        //        quantityFaces = 0;

        currentLine = objectFile.readLine();

        values = currentLine.trimmed().split(' ');
        if (values.size() != 5) // see format file .object
        {
            qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "First line size!=5";
            objectFile.close();
            return Object3d();
        }

        objectResult.setObjectName(values[0]); // set objectName

        // read all vertex from file and write it to object
        {
            uint quantityVertex = values[1].toUInt(); // get quantity vertex
            for (uint i = 0; i < quantityVertex; i++) // parse all lines that contain vertex
            {
                currentLine = objectFile.readLine();
                tempValues = currentLine.trimmed().split(' '); // parse each line on vertex coords
                if (tempValues.size() != 3)
                {
                    qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "Vertex size!=3";
                    objectFile.close();
                    return Object3d();
                }
                objectResult.addVertex3d({ tempValues[0].toFloat(), tempValues[1].toFloat(),
                                           tempValues[2].toFloat() }); // add vertex to object
            }
        }

        // read all lines from file and write it to object
        {
            uint quantityLines = values[2].toUInt(); // get quantity of lines that contain line data

            for (uint i = 0; i < quantityLines; i++) // parse all lines that contain line data
            {
                currentLine = objectFile.readLine();
                tempValues = currentLine.trimmed().split(' '); // parse line on data
                if (tempValues.size() != 2)
                {
                    qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "Line size!=2";
                    objectFile.close();
                    return Object3d();
                }
                objectResult.addLine3d(
                    { tempValues[0].toUInt(), tempValues[1].toUInt() }); // add line to object array
            }
        }

        // read all triangles from file and write it to object
        {
            uint quantityTriangles = values[3].toUInt(); // get quantity triangles
            for (uint i = 0; i < quantityTriangles; i++) // parse data on triangles
            {
                currentLine = objectFile.readLine();
                tempValues = currentLine.trimmed().split(' ');
                if (tempValues.size() != 3)
                {
                    qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "Triangles size!=3";
                    objectFile.close();
                    return Object3d();
                }
                // add triangle in object array
                objectResult.addTriangle3d(
                    { 0, tempValues[0].toUInt(), tempValues[1].toUInt(),
                      tempValues[2].toUInt() }); // need to add normal as first element!!!
            }
        }

        // read all faces from file and write it to object
        {
            uint quantityFaces = values[4].toUInt(); // get quantity faces
            for (uint i = 0; i < quantityFaces; i++) // parse data on faces
            {
                currentLine = objectFile.readLine();
                tempValues = currentLine.trimmed().split(' ');
                if (tempValues.size() != 4)
                {
                    qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "Faces size!=4";
                    objectFile.close();
                    return Object3d();
                }
                // add face to object faces array
                objectResult.addFace3d({ 0, tempValues[0].toUInt(), tempValues[1].toUInt(),
                                         tempValues[2].toUInt(),
                                         tempValues[3].toUInt() }); // need to add normal as first element!!!
            }
        }
        objectFile.close();
        return objectResult; // return object that filled all data
    }
    else
        qDebug() << __FILE__ << __LINE__ << __FUNCTION__ << "Can't open the file " << objectFile;
    return Object3d();
}

Object3d ObjectStorageManager::getObjectFromListByIndex(uint objectIndex)
{
    if (objectIndex >= objectsList.size())
        return Object3d();

    return getObjectFromListByName(objectsList[objectIndex]);
}

std::vector<QString> ObjectStorageManager::getObjectsList() const
{
    return objectsList;
}

QString ObjectStorageManager::findUniqueFileName(QString path)
{
    QFile tempFile;
    int i = -1;
    do
    {
        tempFile.setFileName(path + QString::number(++i) + ".object");

    } while (tempFile.exists());
    return path + QString::number(i) + ".object";
}

void ObjectStorageManager::Initialize()
{
    loadObjectsToList();
}

void ObjectStorageManager::loadObjectsToList()
{
    if (!QDir(objectStorageDir).exists())
        return;

    QStringList objectList = QDir(objectStorageDir).entryList(QDir::Files);
    for (auto objectName : objectList)
        objectsList.push_back(objectName.split('.')[0]);
}

ObjectStorageManager::~ObjectStorageManager()
{
}
