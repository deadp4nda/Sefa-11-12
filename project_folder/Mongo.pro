TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = MongoApplication\
		  MongoLib

MongoApplication.depends = MongoLib
