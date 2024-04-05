DROP TABLE STUDENT CASCADE CONSTRAINTS;
DROP TABLE ADVISOR CASCADE CONSTRAINTS; 
DROP TABLE ALUMN CASCADE CONSTRAINTS;
DROP TABLE MENTOR CASCADE CONSTRAINTS;


CREATE TABLE STUDENT (
        StudentID           NUMBER              PRIMARY KEY,
        LastName            VARCHAR2(30)        NOT NULL,
        FirstName           VARCHAR2(30)        NOT NULL,
        Email               VARCHAR2(100)       CONSTRAINT STUDENTemailFormat CHECK (email LIKE '%@students.hu.edu') NOT NULL,
        DormName            VARCHAR2(30)        NOT NULL,
        RoomNumber          NUMBER              NOT NULL,
        Phone               VARCHAR2(12)        NOT NULL,
        AdvisorID           NUMBER              NOT NULL,
        MentorID            NUMBER
        /*
        CONSTRAINT FK_STUDENT_ADV FOREIGN KEY(AdvisorID) REFERENCES ADVISOR(AdvisorID),
        CONSTRAINT FK_STUDENT_MTR FOREIGN KEY(MentorID) REFERENCES MENTOR(MentorID)
        */
        );
    
CREATE TABLE ADVISOR (
        AdvisorID           NUMBER              PRIMARY KEY,
        LastName            VARCHAR2(30)        NOT NULL,
        FirstName           VARCHAR2(30)        NOT NULL,
        Email               VARCHAR2(100)       CONSTRAINT ADVISORemailFormat CHECK (email LIKE '%@.hu.edu') NOT NULL,
        Department          VARCHAR2(30)        NOT NULL,
        BuildingName        VARCHAR2(30)        NOT NULL,
        RoomNumber          NUMBER              NOT NULL,
        OfficePhone         VARCHAR2(12)        NOT NULL
        );
    
CREATE TABLE ALUMN (
        StudentID           NUMBER              PRIMARY KEY,
        LastName            VARCHAR2(30)        NOT NULL,
        FirstName           VARCHAR2(30)        NOT NULL,
        Email               VARCHAR2(100)       CONSTRAINT ALUMNemailFormat CHECK (email LIKE '%@somewhere.com') NOT NULL,
        Address             VARCHAR2(100)       NOT NULL,
        City                VARCHAR2(30)        NOT NULL,
        State               VARCHAR2(2)         NOT NULL,
        ZipCode             NUMBER(5,0)         NOT NULL,
        Phone               VARCHAR2(12)        NOT NULL,
        MentorID            NUMBER
        /*
        CONSTRAINT FK_ALUMN_MTR FOREIGN KEY(MentorID) REFERENCES MENTOR(MentorID)
        */
        );

CREATE TABLE MENTOR (
        MentorID            NUMBER              PRIMARY KEY,
        LastName            VARCHAR2(30)        NOT NULL,
        FirstName           VARCHAR2(30)        NOT NULL,
        Email               VARCHAR2(100)       CONSTRAINT MENTORemailFormat CHECK (email LIKE '%@companyname.com') NOT NULL,
        CompanyName         VARCHAR2(100)       NOT NULL,
        CompanyAddress      VARCHAR2(100)       NOT NULL,
        CompanyCity         VARCHAR2(30)        NOT NULL,
        CompanyState        VARCHAR2(2)         NOT NULL,
        CompanyZip          NUMBER(5,0)         NOT NULL,
        CompanyPhone        VARCHAR2(12)        NOT NULL,
        IsAlumn             VARCHAR2(3)         CHECK (IsALumn IN ('Yes', 'No')), 
        AdvisorID           NUMBER              NOT NULL
        /*
        CONSTRAINT FK_MENTOR_ADV FOREIGN KEY(AdvisorID) REFERENCES ADVISOR(AdvisorID),
        */
        );

INSERT INTO STUDENT VALUES (100, 'Doe', 'Jane', 'Jane.Doe@students.hu.edu', 'Dorm A', 301, '987-654-3210', 1, 1);
INSERT INTO STUDENT VALUES (105, 'Lee', 'Michael', 'Michael.Lee@students.hu.edu', 'Dorm B', 302, '876-543-2109', 2, 2);
INSERT INTO STUDENT VALUES (110, 'Clark', 'Emma', 'Emma.Clark@students.hu.edu', 'Dorm C', 303, '765-432-1098', 3, 3);
INSERT INTO STUDENT VALUES (115, 'Lewis', 'Daniel', 'Daniel.Lewis@students.hu.edu', 'Dorm D', 304, '654-321-0987', 4, 4);
INSERT INTO STUDENT VALUES (120, 'Walker', 'Olivia', 'Olivia.Walker@students.hu.edu', 'Dorm E', 305, '543-210-9876', 5, 5);

INSERT INTO ADVISOR VALUES (1, 'Smith', 'John', 'John.Smith@.hu.edu', 'Mathematics', 'Building A', 101, '123-456-7890');
INSERT INTO ADVISOR VALUES (2, 'Johnson', 'James', 'James.Johnson@.hu.edu', 'Physics', 'Building B', 202, '234-567-8901');
INSERT INTO ADVISOR VALUES (3, 'Williams', 'Kathy', 'Kathy.Williams@.hu.edu', 'Chemistry', 'Building C', 303, '345-678-9012');
INSERT INTO ADVISOR VALUES (4, 'Brown', 'Sarah', 'Sarah.Brown@.hu.edu', 'Biology', 'Building D', 404, '456-789-0123');
INSERT INTO ADVISOR VALUES (5, 'Taylor', 'Brian', 'Brian.Taylor@.hu.edu', 'Computer Science', 'Building E', 505, '567-890-1234');

INSERT INTO ALUMN VALUES (10, 'Johnson', 'Emily', 'Emily.Johnson@somewhere.com', '123 Main St', 'Seattle', 'WA', 98101, '111-222-3333', 1);
INSERT INTO ALUMN VALUES (15, 'Moore', 'William', 'William.Moore@somewhere.com', '456 First St', 'Tacoma', 'WA', 98402, '222-333-4444', 2);
INSERT INTO ALUMN VALUES (20, 'Anderson', 'Linda', 'Linda.Anderson@somewhere.com', '789 Second St', 'Olympia', 'WA', 98503, '333-444-5555', 3);
INSERT INTO ALUMN VALUES (25, 'Hall', 'Robert', 'Robert.Hall@somewhere.com', '321 Third St', 'Spokane', 'WA', 99204, '444-555-6666', 4);
INSERT INTO ALUMN VALUES (30, 'Thomas', 'Nancy', 'Nancy.Thomas@somewhere.com', '654 Fourth St', 'Kent', 'WA', 98005, '555-666-7777', 5);

INSERT INTO MENTOR VALUES (1, 'Brown', 'David', 'David.Brown@companyname.com', 'Pinnacle Consulting', '456 Pinnacle Dr', 'Bellevue', 'WA', 98004, '555-666-7777', 'Yes', 1);
INSERT INTO MENTOR VALUES (2, 'Davis', 'Sophia', 'Sophia.Davis@companyname.com', 'Academic Group', '123 Academic St', 'Seattle', 'WA', 98105, '666-777-8888', 'No', 2);
INSERT INTO MENTOR VALUES (3, 'Miller', 'Christopher', 'Christopher.Miller@companyname.com', 'Scholar Mentoring', '789 Scholar Dr', 'Tacoma', 'WA', 98406, '777-888-9999', 'Yes', 3);
INSERT INTO MENTOR VALUES (4, 'Wilson', 'Lucas', 'Lucas.Wilson@companyname.com', 'EduTech Advisors', '321 Education Ln', 'Olympia', 'WA', 98507, '888-999-0000', 'No', 4);
INSERT INTO MENTOR VALUES (5, 'Martinez', 'Isabella', 'Isabella.Martinez@companyname.com', 'Pathway Tutors', '654 Tutor Rd', 'Spokane', 'WA', 99208, '999-000-1111', 'Yes', 5);