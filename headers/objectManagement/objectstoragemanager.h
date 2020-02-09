#ifndef OBJECTSTORAGEMANAGER_H
#define OBJECTSTORAGEMANAGER_H
#include <QDebug>
#include <QDir>

#include "object3d.h"
class ObjectStorageManager {
 public:
  ObjectStorageManager(const QByteArray storageName);
  ~ObjectStorageManager();

  QByteArray getObjectStorageDir() const;
  uint getQuantityObjectsInStorage() const;

  bool addNewObject(Object3d newObject);
  void removeObject(QString objectName);

  Object3d getObjectFromListByName(
      QString objectName);  // get 3d object from list by name format:
                            // 'blablabla' without format .object

  Object3d getObjectFromListByIndex(
      uint objectIndex);  // get 3d object from list by index in this list

  std::vector<QString> getObjectsList() const;  // get list of all objects

 private:
  const QByteArray globalObjectStorageName = "objectsStorage/";
  QByteArray objectStorageDir;  // directory name that contain current objects
                                // storage format: objectsStorage/storagedir

  QString findUniqueFileName(
      QString path);  // count filename by 1, while it will non-exist

  std::vector<QString>
      objectsList;  // 3d objects list that loaded during initialization

 private:
  void Initialize();
  void loadObjectsToList();
};

#endif  // OBJECTSTORAGEMANAGER_H
