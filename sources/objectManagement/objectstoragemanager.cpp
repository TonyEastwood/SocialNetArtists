#include "../../headers/objectManagement/objectstoragemanager.h"

ObjectStorageManager::ObjectStorageManager(const QByteArray storageName)
    : objectStorageDir((storageName))
{
    Initialize();
    QDir().mkdir(objectStorageDir.dirName()); // create directory for objects storage
}

QDir ObjectStorageManager::getObjectStorageDir() const
{
    return objectStorageDir;
}

uint ObjectStorageManager::getQuantityObjectsInStorage() const
{
    return objectsList.size();
}

bool ObjectStorageManager::addNewObject(Object3d newObject)
{
    // Format file object:
    // objectName quantityVertex quantityLines quantityTriangles quantityQuads

    QFile newObjectFile(objectStorageDir.path() + '/' + newObject.getName() + ".object");
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
        objectsList.push_back(newObjectFile.fileName());
        return true;
    }
    else
        qDebug() << "[Error] Cannot open the file " << newObject.getName();
    return false;
}

void ObjectStorageManager::Initialize()
{
    loadObjectsToList();
}

void ObjectStorageManager::loadObjectsToList()
{
    if (!objectStorageDir.exists())
        return;

    QStringList objectList = objectStorageDir.entryList(QDir::Files);
    for (auto objectName : objectList)
        objectsList.push_back(objectName);
}
ObjectStorageManager::~ObjectStorageManager()
{
}
