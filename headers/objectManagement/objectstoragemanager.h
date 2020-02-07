#ifndef OBJECTSTORAGEMANAGER_H
#define OBJECTSTORAGEMANAGER_H
#include <QDir>
#include "object3d.h"
#include <QDebug>
class ObjectStorageManager
{
public:
    ObjectStorageManager(const QByteArray storageName); //+
    ~ObjectStorageManager();                            //+

    QByteArray getObjectStorageDir() const;   //+
    uint getQuantityObjectsInStorage() const; //+

    bool addNewObject(Object3d newObject); //+

    Object3d getObjectFromListByName(
        QString objectName); // get 3d object from list by name format: 'blablabla' without format .object

    std::vector<QString> getObjectsList() const; // get list of all objects

private:
    const QByteArray globalObjectStorageName = "objectsStorage/";
    QByteArray objectStorageDir; // directory name that contain current objects storage

    std::vector<QString> objectsList; // 3d objects list that loaded during initialization

private:
    void Initialize();        //+
    void loadObjectsToList(); //+
};

#endif // OBJECTSTORAGEMANAGER_H
