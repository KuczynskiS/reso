<?php
require_once("classdef.inc");


// Log in and getting user data
//



function UserId($U_Login,$U_pass);
{
	$Client=new User;
	return $Client->GetUser($U_Login,$U_pass));
	
}

function Login($U_Login,$U_pass);
{
	$Client=new User;
	$Client->SetUser($Client->GetUser($U_Login,$U_pass));
	return $Client->GetUserPriv($Client->UserId);	
}


function StartKoszyk($U_Id);
{
	$NowyKoszyk= new Basket;
	return $NowyKoszyk->GetBasketId();
}


//START
// HTML form is sendind variable login i password by POST method
public $ClientPriv;
public $ClientId;
public $KoszykId;

$ClientPriv=Login($_POST['login'],$_POST['password']);
$ClientId=UserId($_POST['login'],$_POST['password']);

// Initializng new basket
$KoszykId=StartKoszyk($ClientId);


// Adding new items to basket ie. using HTML form and variable Item,Quiantity,Media and sending to PHP by POST method
//  It can be triggered in HTML form on even Clikc on <INPUT Type=BUTTON > control

$Koszyk=new Basket;

$Koszyk->SetBasketId($KoszykId);

if !($Koszyk->AddBasketItem($KoszykId,$_POST['Item'],$_POST['Quantity'],$_POST['Media'],$ClientId,$ClientPriv)
{
echo "Nie mogê dodac wiêcej rekordów";
}


// Storing basket as new order
//

$Zamowienie=new Order();

$Zamowienie->SetNewOrder($KoszykId,$ClientId);

//Copy basket content to order 

$Zamowienie->SetOrderFromBasket($KoszykId);

//Calculating discount and storing new value of order
$Zamowienie->SetOrderDiscount($KoszykId);



if ($Zamowienie->FinishOrder($Zamowienie->GetOrderId($KoszykId)))
	{
	echo "Zamówienie z³o¿one";
	}
else
	{
	echo " Nie mogê zapisaæ zamówienia";
	}

//END





?>
