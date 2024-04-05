/********************************************************************************/
/*																				*/
/*	Kroenk, Auer, Vandenberg & Yoder											*/
/*  Database Concepts (8th Edition) Chapters 06, 07, 08							*/
/*																				*/
/*	Marcia's Dry Cleaning [MDC] Create Tables									*/
/*																				*/
/*	Oracle Database XE code solutions											*/
/*																				*/
/********************************************************************************/

CREATE TABLE CLIENT (
		ClientID			NUMBER PRIMARY KEY,
		FirstName 			VARCHAR2(25)		NOT NULL,
		LastName			VARCHAR2(25)		NOT NULL,
		Phone				VARCHAR2(12)		NOT NULL,
		EmailAddress		VARCHAR2(100)		NULL
		); 

CREATE SEQUENCE seqCID INCREMENT BY 5 START WITH 100;		
	
CREATE TABLE SERVICE (
		ServiceID		    NUMBER				NOT NULL PRIMARY KEY,
		ServiceDescription	VARCHAR2(50)		NOT NULL,
		UnitPrice			NUMBER(8,2)		NOT NULL,
		CONSTRAINT check_unit_price	CHECK 
							((UnitPrice >= 1.50) AND (UnitPrice <= 10.00))
		);

CREATE TABLE INVOICE (
		InvoiceNumber		NUMBER				NOT NULL,
		ClientID			NUMBER				NOT NULL,
		DateIn				Date			NOT NULL,
		DateOut				Date			NULL,
		Subtotal			NUMBER(8,2)		NULL,
		Tax					NUMBER(8,2)		NULL,
		TotalAmount			NUMBER(8,2)		NULL,
		PRIMARY KEY (InvoiceNumber),
		CONSTRAINT	FK_INVOICE_CLNT FOREIGN KEY(ClientID)
								REFERENCES CLIENT(ClientID)
		);

CREATE TABLE INVOICE_ITEM (
		InvoiceNumber		NUMBER				NOT NULL,
		ItemNumber			NUMBER				NOT NULL,
		ServiceID			NUMBER				NOT NULL,
		Quantity			NUMBER				DEFAULT 1 NOT NULL,
		UnitPrice			NUMBER(8,2)		NULL,
		ExtendedPrice		NUMBER(8,2)		NULL,
		PRIMARY KEY(InvoiceNumber, ItemNumber),
		CONSTRAINT FK_INVOICEITEM_INVOICE FOREIGN KEY(InvoiceNumber)
								REFERENCES INVOICE(InvoiceNumber)
									ON DELETE CASCADE,
		CONSTRAINT FK_INVOICEITEM_SERVICE FOREIGN KEY(ServiceID)
								REFERENCES Service(ServiceID)
		);
	

/******************************************************************************/



