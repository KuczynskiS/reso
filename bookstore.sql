CREATE DATABASE  IF NOT EXISTS `bookstore` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `bookstore`;
DROP TABLE IF EXISTS `basket`;
CREATE TABLE `basket` (
  `BaskId` int(11) NOT NULL AUTO_INCREMENT,
  `BaskTranId` varchar(45) DEFAULT NULL,
  `BaskTranItem` varchar(45) DEFAULT NULL,
  `BaskTranQuant` varchar(45) DEFAULT NULL,
  `BaskTranPrice` decimal(5,2) DEFAULT NULL,
  `BaskTranAddInfo` varchar(45) DEFAULT NULL,
  `BaskDelTime` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `BaskUserId` int(11) DEFAULT NULL,
  PRIMARY KEY (`BaskId`),
  UNIQUE KEY `BasketId_UNIQUE` (`BaskId`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8;

LOCK TABLES `basket` WRITE;
INSERT INTO `basket` VALUES (1,'ABCDEFGHIJK','1','1',59.99,'Paper','0000-00-00 00:00:00',1),(2,'ABCDEFGHIJK','3','2',33.33,'Cd','0000-00-00 00:00:00',1),(3,'ABCDEFGHIJK','4','1',88.88,'Lp','0000-00-00 00:00:00',1),(4,'XYZQWERTYUIO','5','2',44.44,'Cd','0000-00-00 00:00:00',2),(5,'XYZQWERTYUIO','6','1',22.22,'Dvd','0000-00-00 00:00:00',2),(6,'XYZQWERTYUIO','7','1',66.66,'Blue-Ray','0000-00-00 00:00:00',2),(7,'XYZQWERTYUIO','8','3',77.77,'Dvd','0000-00-00 00:00:00',2),(8,'XYZQWERTYUIO','9','1',11.11,'Lp','0000-00-00 00:00:00',2);
UNLOCK TABLES;


DROP TABLE IF EXISTS `item`;
CREATE TABLE `item` (
  `ItemId` int(11) NOT NULL AUTO_INCREMENT,
  `ItemName` varchar(45) DEFAULT NULL,
  `ItemDesc` varchar(45) DEFAULT NULL,
  `ItemType` varchar(45) DEFAULT NULL,
  `ItemCode` varchar(45) DEFAULT NULL,
  `ItemPrice` decimal(5,2) DEFAULT NULL,
  PRIMARY KEY (`ItemId`),
  UNIQUE KEY `ItemId_UNIQUE` (`ItemId`),
  KEY `Name` (`ItemName`),
  KEY `Code` (`ItemCode`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8;

LOCK TABLES `item` WRITE;
/*!40000 ALTER TABLE `item` DISABLE KEYS */;
INSERT INTO `item` VALUES (1,'Book Title 1 - Author 1','Something about book 1','B','111-2-33-444444-5',99.99),(2,'Book Title 2 - Author 2','Something about book 2','B','555-4-33-222222-1',55.55),(3,'Music 1 - Band 1','Nice music 1','M',NULL,33.33),(4,'Music 2 - orchestra 1','Very nice music','M',NULL,88.88),(5,'Good Movie 1','Very good adventure movie','F',NULL,44.44),(6,'Scary movie','Do not show to children','F',NULL,22.22),(7,'Fantastic movie','Good for children','F',NULL,66.66),(8,'Family movie','Watch with family','F',NULL,77.77),(9,'Music 3 - jazzband','Old jazz style','M',NULL,11.11);
/*!40000 ALTER TABLE `item` ENABLE KEYS */;
UNLOCK TABLES;

DROP TABLE IF EXISTS `media`;
CREATE TABLE `media` (
  `MediaId` int(11) NOT NULL AUTO_INCREMENT,
  `MediaType` varchar(45) DEFAULT NULL,
  `ItemType` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`MediaId`),
  UNIQUE KEY `MediaId_UNIQUE` (`MediaId`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8;

LOCK TABLES `media` WRITE;
INSERT INTO `media` VALUES (1,'Paper','B'),(2,'Cd','F'),(3,'Dvd','F'),(4,'Blue-Ray','F'),(5,'Cd','M'),(6,'Lp','M');
UNLOCK TABLES;

DROP TABLE IF EXISTS `order_items`;
CREATE TABLE `order_items` (
  `OrdPosId` int(11) NOT NULL AUTO_INCREMENT,
  `OrderId` int(11) DEFAULT NULL,
  `OrderItemId` varchar(45) DEFAULT NULL,
  `OrderQuant` smallint(5) unsigned DEFAULT '0',
  `OrderItemAddInfo` varchar(45) DEFAULT NULL,
  `OrderItemPrice` decimal(5,2) DEFAULT NULL,
  PRIMARY KEY (`OrdPosId`),
  UNIQUE KEY `OrderId_UNIQUE` (`OrdPosId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;


LOCK TABLES `order_items` WRITE;
UNLOCK TABLES;


DROP TABLE IF EXISTS `orders`;
CREATE TABLE `orders` (
  `OrderId` int(11) NOT NULL AUTO_INCREMENT,
  `OrderTime` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `OrderStatus` tinyint(3) unsigned DEFAULT NULL,
  `OrderValue` decimal(5,2) DEFAULT NULL,
  `OrderNumber` varchar(45) DEFAULT NULL,
  `UserId` int(11) DEFAULT NULL,
  `BaskTranId` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`OrderId`),
  UNIQUE KEY `OrderId_UNIQUE` (`OrderId`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;

LOCK TABLES `orders` WRITE;
INSERT INTO `orders` VALUES (1,'2019-07-11 12:53:15',1,215.53,'1/2019',1,'ABCDEFGHIJK');
UNLOCK TABLES;

DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `UserId` int(11) NOT NULL AUTO_INCREMENT,
  `UserName` varchar(45) DEFAULT NULL,
  `UserLogin` varchar(45) DEFAULT NULL,
  `UserPass` varchar(45) DEFAULT NULL,
  `UserPriv` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`UserId`),
  UNIQUE KEY `UserId_UNIQUE` (`UserId`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

LOCK TABLES `user` WRITE;

INSERT INTO `user` VALUES (1,'User Name 1','user1','secretpass1','ADD_ORDER'),(2,'User Name 2','user2','secretpas2','MANAGE_ORDER'),(3,'User Name 3','user3','secretpass3','ADD_ORDER');
UNLOCK TABLES;

/* Zmiana w gicie*/
