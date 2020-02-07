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

    QDir getObjectStorageDir() const;         //+
    uint getQuantityObjectsInStorage() const; //+

    bool addNewObject(Object3d newObject);

private:
    QDir objectStorageDir; // directory name that contain current objects storage

    std::vector<QString> objectsList; // 3d objects list that loaded during initialization

private:
    void Initialize();        //+
    void loadObjectsToList(); //+
};

#endif // OBJECTSTORAGEMANAGER_H
