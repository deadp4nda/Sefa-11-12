TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = MongoLib\
            MongoApplication

MongoApplication.depends = MongoLib
