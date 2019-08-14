<?php
//definicje klas

require_once("db.inc");

public $DbHost = 'localhost';
public $DdUser = 'sqluser';
public $DbPass = 'secretpass';
public $DbName = 'bookstore';


class Item
{

	private $ItemId;
	private $ItemName;
	private $ItemQuant;
	private $ItemPrice;
	private $ItemAddInfo;

	public function __construct()
	{
	$this->ItemId=0;
	$this->ItemName="";
	$this->ItemQuant=0;
	$this->ItemPrice=0;
	$this->ItemAddInfo="";
	}

	public function SetItem($I_Id,$I_Name,$I_Quant,$I_Price,$I_Addinf)
	{
		$this->ItemId=$I_id;
		$this->ItemName=$I_Name;
		$this->ItemQuant=$I_Quant;
		$this->ItemPrice=$I_Price;
		$this->ItemInfo=$I_Addinf;
	}

}

// end Item

class User
{
	
	private $UserId;
	private $UserName;
	private $UserPriv;

	public function __construct()
	{
	$this->UserId=0;
	$this->UserName="";
	$this->UserPriv="";
	}

	public function SetUser($U_Id)
	{
		
		$Db = new db($DbHost, $DbUser, $DbPass, $DbName);

		$QueryRessult=$Db->Query("SELECT * FROM user WHERE UserId = ? ",$U_Id)->FetchArray();
		$this->UserId=$QueryResult['UserId'];
		$this->UserName=$QueryResult['UserName'];
		$this->UserPriv=$QueryResult['UserPriv'];

		$Db->Close();

	}

	public function GetUser($U_Login,$U_Pass)
	{
		
		$Db = new db($DbHost, $DbUser, $DbPass, $DbName);

		$QueryRessult=$Db->Query("SELECT UserId FROM user WHERE ( UserLogin LIKE '?' AND UserPass LIKE '?' ) ",$U_Login,$U_Pass)->FetchArray();
		$this->UserId=$QueryResult['UserId'];
		
		$Db->Close();
		
		return $this->$UserId;

		
	}

	public function GetUserPriv($U_Id)
	}
			
		$Db = new db($DbHost, $DbUser, $DbPass, $DbName);

		$QueryRessult=$Db->Query("SELECT UserPriv FROM user WHERE UserId =?",$U_Id)->FetchArray();
		$this->UserPriv=$QueryResult['UserPriv'];
		
		$Db->Close();

		return $this->$UserPriv;
	}

}

// end User


class Basket
{

	// Class basket with methods
	//
	private $BaskTranId;
	private $BaskUserId;
	private $BakTranItem;
	private $BaskTranQuant;
	private $BaskTranPrice;
	private $BaskTranAddInfo;

	public function __construct()
	{
	$this->BaskTranId="";
	$this->BaskUserId=0;
	$this->BakTranItem=0;
	$this->BaskTranQuant=0;
	$this->BaskTranPrice=0;
	$this->BaskTranAddInfo="";
	}

	public function GetBasketId()
	{
		//Generate ASCII unique basket transaction Id
		
		for ($Count=1;$Count<=12;$Count++)
		{
			$this->BaskTranId.=chr( $rand(65,102) );
		}
		return $this->BaskTranId;	
	}


	public function SetBasketId($B_Id)
	{
		
		$this->BaskTranId=$B_Id;
		return $this->BaskTranId;	
	}


	public function GetBasketItem($B_Id)
	{
		$Db = new db($DbHost, $DbUser, $DbPass, $DbName);

		$QueryResult= $Db->Query("SELECT * FROM basket WHERE BaskId= ?",$B_Id)->FetchArray();
		$this->BaskTranItem=$QueryResult['BaskTranItem'];
		return $this->BaskTranItem;	

		$Db->Close();
	}

	public function AddBasketItem($B_TranId,$I_Id,$I_Quant,$M_Type,$U_Id,$U_Priv)
	{
		//Add new item to basket 
		$UserRecordNo=0;

		
		$Db = new db($DbHost, $DbUser, $DbPass, $DbName);

		$QueryResult= $Db-Query("SELECT COUNT(*) AS RecCount FROM basket WHERE BaskTranId= ? AND BaskDelTime <>'0000-00-00 00:00:00' ",$B_TranId)->FetchArray();		
		$UserRecordNo=$QueryResult['RecCount'];


		$QueryResult= $Db-Query("SELECT * FROM item WHERE ItemId= ?",$I_Id)->FetchArray();

		$this->BaskTranId=$B_TranId;
		$this->BaskUserId=$U_Id;
		$this->BakTranItem=$I_Id;
		$this->BaskTranQuant=$I_Quant;
		$this->BaskTranPrice=$QueryResult['ItemPrice'];
		$this->BaskTranAddInfo=$M_Type;

		// Control of items count in basket depending on user privileges
		
		if   ( ($U_Priv=="ADD_ORDER") && ($UserRecordNo>=3) )
		{
		$InsertResult = $Db->Query("INSERT INTO basket (BaskTranId,BaskTranItem,BaskTranQuant,BaskTranPrice,BaskTranAddInfo,BaskUserId) VALUES (?,?,?,?,?)",$this->BasketTranId,$this->BaskTranItem,$this->BaskTranQuant,$this->BaskTranPrice,$this->BaskTranAddInfo,$this->BaskUserId);
		}
		elseif ($U_Priv=="MANAGE_ORDER")
		{
		$InsertResult = $Db->Query("INSERT INTO basket (BaskTranId,BaskTranItem,BaskTranQuant,BaskTranPrice,BaskTranAddInfo,BaskUserId) VALUES (?,?,?,?,?)",$this->BasketTranId,$this->BaskTranItem,$this->BaskTranQuant,$this->BaskTranPrice,$this->BaskTranAddInfo,$this->BaskUserId);
		}

		if ($Db->AffectedRows()>0)
		{
			$Db->Close();
			return TRUE;
		}
		else
		{
			$Db->Close();
			return FALSE;
		}
		

	}


} 
//end basket



class Order
{
	// Clas for orders
	private $OrdNumber;
	private $OrdPrice;
	private $OrdTime;
	private $OrdStatus;
	private $OrdValue;
	private $OrdUserId;
	private $OrdBaskTranId;
	private $OrdId;

	public function __construct()
	{
	
	$this->OrdNumber="";
	$this->OrdTime="0000-00-00 00:00:00";
	$this->OrdStatus=0;
	$this->OrdValue=0;
	$this->OrdUserId=0;
	$this->OrdBaskTranId="";
	$this->OrdId=0;

	}


	public function SetNewOrder($B_Id,$U_Id)
	{
		
		$Db = new db($DbHost, $DbUser, $DbPass, $DbName);
		
		$QueryResult= $Db-Query("SELECT NOW() AS Czas")->FetchArray();
		
		$this->OrdTime=$QueryResult['Czas'];
		
		// Set OrderStatus 1 - new 
		$this->OrdStatus=1;

		$QueryResult= $Db-Query("SELECT MAX(OrderId) AS MxOrdId,YEAR(NOW()) AS Rok")->FetchArray();
		$this->OrderNumber=$QueryResult['MxOrdId']."/".$QueryResult['Rok'];
		$this->OrdValue=0;
		$this->OrdUserId=$U_Id;
		$this->OrdBaskTranId=$B_id;

		$Db->StartTran();
		
		$InsertResult = $Db->Query("INSERT INTO order (OrderNumber,OrderTime,OrderStatus,OrderValue,UserId,BaskTranId) VALUES (?,NOW(),?,?,?,?)",$this->OrderNumber,$this->OrderStatus,$this->OrderValue,$this->OrdUserId,$this->OrdBaskTranId);

		if !($Db->CommitTran())
		{
			$Db->RollTran();
		}

		$Db->Close();

	}



	public function GetOrderId($B_Id)
	{
		$Db = new db($DbHost, $DbUser, $DbPass, $DbName);
		
		$QueryResult=$Db->Query("SELECT OrderId FROM orders WHERE BaskTranId LIKE '?'",$B_Id)->FetchArray();
		
		// Basket Value
		$O_Id=$QueryResult['OrderId'];

		return $O_Id;	

		$Db->Close();


	}


	public function SetOrderFromBasket($B_Id);
	{

		$Db = new db($DbHost, $DbUser, $DbPass, $DbName);
		
		$QueryResult= $Db->Query("SELECT OrderId FROM Order WHERE BaskTranId=?",$B_id)->FetchArray();
		
		$this->OrdId=$QueryResult['OrderId'];

		$Db->StartTran();

		$InsertResult=$Db->Query("INSERT INTO order_items (OrderId,OrderItemId,OrderQuant,OrderItemAddInfo,OrderItemPrice) SELECT (?,BaskTranItem,BaskTranQuant,BaskTranAddInfo,BaskTranPrice) FROM basket WHERE BaskTranId=? AND BaskDelTime LIKE '0000-00-00 00:00:00' ",$this->OrdId,$B_id);

		if !($Db->CommitTran())
		{
			$Db->RollTran();
		}

	
		if ($Db->AffectedRows()>0)
		{

			$Db->Close();
			return TRUE;
		}
		else
		{
			$Db->Close();
			return FALSE;
		}
		


	}


	public function SetOrderDicount($B_Id)
	{
	
		// Discounts for order
	
		$BasketValue=0;	

		$Db = new db($DbHost, $DbUser, $DbPass, $DbName);
		
		$QueryResult=$Db->Query("SELECT SUM(BaskTranQuant*BaskTranPrice) as Suma FROM basket WHERE BaskTranId LIKE '?'",$B_Id)->FetchArray();
		
		// Basket Value
		$BasketValue=$QueryResult['Suma'];

		// Book discount
		$QueryResult=$Db->Query("SELECT Count(b.BaskTranItem) AS Licz , SUM(b.BaskTranQuant*BaskTranPrice) AS Suma FROM basket AS b JOIN item as i ON i.ItemId=b.BaskTranItem WHERE b.BaskTranId LIKE '?' AND i.ItemType LIKE 'B' ",$B_Id)->FetchArray();
	
		$BookValue=$QueryResult['Suma'];

		$BookCount=$QueryResult['Licz'];

		if ($BookCount>=3)
		{
			$BasketValue=$BasketValue-($BookValue*0.15);
		}	


		// Music discount
		$QueryResult=$Db->Query("SELECT Count(b.BaskTranItem) AS Licz , SUM(b.BaskTranQuant*BaskTranPrice) AS Suma FROM basket AS b JOIN item as i ON i.ItemId=b.BaskTranItem WHERE b.BaskTranId LIKE '?' AND i.ItemType LIKE 'M' ",$B_Id)->FetchArray();

		$MusicValue=$QueryResult['Suma'];

		$MusicCount=$QueryResult['Licz'];

		if ($MusicCount>=3)
		{
			$BasketValue=$BasketValue-($MusicValue*0.1);
		}


		// Movie discount
		$QueryResult=$Db->Query("SELECT Count(b.BaskTranItem) AS Licz , SUM(b.BaskTranQuant*BaskTranPrice) AS Suma FROM basket AS b JOIN item as i ON i.ItemId=b.BaskTranItem WHERE b.BaskTranId LIKE '?' AND i.ItemType LIKE 'F' ",$B_Id)->FetchArray();

		$FIlmValue=$QueryResult['Suma'];

		$FilmCount=$QueryResult['Licz'];

		if ($FilmCount>=3)
		{
			$BasketValue=$BasketValue-15;
		}
		
		// if basket value less than 0 set 1 to pln (according to law)
		if ($BasketValue<0)
		{
			$BasketValue=1;
		}

		// Calculate and Store new order value
		//

		$QueryResult=$Db->Query("UPDATE orders SET OrderValue=?,OrderStatus=2 WHERE OrderId=? AND BaskTranId=? LIMIT 1",$BasketValue,$this->OrdId,$B_id);

		$Db->Close();


	}
	



	public function FinishOrder($O_Id)
	{
		// Finishing order set status=3
		$Db = new db($DbHost, $DbUser, $DbPass, $DbName);
		
		$QueryResult=$Db->Query("UPDATE orders SET OrderStatus=3,OrderTime=NOW() WHERE OrderId=? AND BaskTranId=? LIMIT 1",$O_id);
		
		if ($Db->AffectedRows()>0)
		{
			$Db->Close();
			return TRUE;
		}
		else
		{
			$Db->Close();
			return FALSE;
		}
	}

}
// end Order


?>



