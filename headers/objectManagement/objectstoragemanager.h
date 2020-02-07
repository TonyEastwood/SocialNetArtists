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

    bool addNewObject(Object3d newObject);

    Object3d getObjectFromListByIndex(uint objectIndex);  // get 3d object from list by index
    Object3d getObjectFromListByName(QString objectName); // get 3d object from list by name

private:
    QByteArray objectStorageDir; // directory name that contain current objects storage

    std::vector<QString> objectsList; // 3d objects list that loaded during initialization

private:
    void Initialize();                            //+
    void loadObjectsToList();                     //+
    Object3d getObjectByName(QString objectName); // get name format 'blablabla' without format .object
};

#endif // OBJECTSTORAGEMANAGER_H
