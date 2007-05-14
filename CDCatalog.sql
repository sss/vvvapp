/******************************************************************************/
/****         Generated by IBExpert 2006.12.13 14/05/2007 16.57.04         ****/
/******************************************************************************/

SET SQL DIALECT 3;

SET NAMES NONE;

CREATE DATABASE 'E:\C_Prg\vvv (virtual volumes view)\CDCatalog.vvv'
USER 'SYSDBA' PASSWORD 'masterkey'
PAGE_SIZE 4096
DEFAULT CHARACTER SET NONE;



/******************************************************************************/
/****                              Generators                              ****/
/******************************************************************************/

CREATE GENERATOR GEN_FILES_ID;
CREATE GENERATOR GEN_PATHS_ID;
CREATE GENERATOR GEN_VIRTUAL_FILES_ID;
CREATE GENERATOR GEN_VIRTUAL_PATHS_ID;
CREATE GENERATOR GEN_VOLUMES_ID;


/******************************************************************************/
/****                              Exceptions                              ****/
/******************************************************************************/

CREATE EXCEPTION EX_RENAME_PHYSICAL_PATH 'Unable to rename a virtual path with a link to a physical path';



SET TERM ^ ; 



/******************************************************************************/
/****                          Stored Procedures                           ****/
/******************************************************************************/

CREATE PROCEDURE SP_ADD_PHYSFILE_TO_VIRTUALPATH (
    PHYS_FILE_ID BIGINT,
    VIRTUAL_PATH_ID BIGINT)
AS
BEGIN
  EXIT;
END^


CREATE PROCEDURE SP_ADD_PHYSPATH_TO_VIRTUALPATH (
    PHYS_PATH_ID BIGINT,
    VIRTUAL_PATH_ID BIGINT)
AS
BEGIN
  EXIT;
END^


CREATE PROCEDURE SP_ADD_VOLUME_TO_VIRTUALPATH (
    VOLUME_ID BIGINT,
    PHYS_PATH_ID BIGINT,
    VIRTUAL_PATH_ID BIGINT)
AS
BEGIN
  EXIT;
END^


CREATE PROCEDURE SP_APPEND_PHYSPTH_TO_VIRTUALPTH (
    PHYS_PATH_ID BIGINT,
    VIRTUAL_PATH_ID BIGINT)
AS
BEGIN
  EXIT;
END^


CREATE PROCEDURE SP_CREATE_UNIQUE_VIRTUALPATH (
    PATH_NAME VARCHAR(500),
    FATHER_ID BIGINT,
    PHYS_PATH_ID BIGINT)
RETURNS (
    VPATH_ID BIGINT)
AS
BEGIN
  EXIT;
END^


CREATE PROCEDURE SP_CREATE_VIRTUALPATH (
    PATH_NAME VARCHAR(500),
    FATHER_ID BIGINT,
    PHYS_PATH_ID BIGINT,
    CREATE_VIRTUAL_FOLDER_FILE SMALLINT)
RETURNS (
    VPATH_ID BIGINT)
AS
BEGIN
  EXIT;
END^


CREATE PROCEDURE SP_DELETE_VIRTUAL_FOLDER (
    VIRTUAL_PATH_ID BIGINT)
AS
BEGIN
  EXIT;
END^


CREATE PROCEDURE SP_DELETE_VOLUME (
    VOLUME_ID BIGINT)
AS
BEGIN
  EXIT;
END^


CREATE PROCEDURE SP_GET_FULL_PATH (
    PHYS_PATH_ID BIGINT,
    PATH_SEPARATOR VARCHAR(5))
RETURNS (
    FULL_PATH VARCHAR(500))
AS
BEGIN
  EXIT;
END^


CREATE PROCEDURE SP_GET_PHYS_FILEID_FROM_PATHID (
    PATH_ID BIGINT)
RETURNS (
    FILE_ID BIGINT)
AS
BEGIN
  EXIT;
END^


CREATE PROCEDURE SP_RENAME_VIRTUALPATH (
    VPATH_ID BIGINT,
    PATH_NAME VARCHAR(500))
RETURNS (
    STATUS INTEGER)
AS
BEGIN
  EXIT;
END^



SET TERM ; ^


/******************************************************************************/
/****                                Tables                                ****/
/******************************************************************************/



CREATE TABLE FILES (
    FILE_ID        BIGINT NOT NULL,
    FILE_NAME      VARCHAR(500) CHARACTER SET ISO8859_1,
    FILE_SIZE      BIGINT,
    FILE_EXT       VARCHAR(50) CHARACTER SET ISO8859_1,
    FILE_DATETIME  TIMESTAMP,
    PATH_ID        BIGINT,
    PATH_FILE_ID   BIGINT
);

CREATE TABLE PATHS (
    PATH_ID    BIGINT NOT NULL,
    VOLUME_ID  BIGINT NOT NULL,
    PATH_NAME  VARCHAR(500) CHARACTER SET ISO8859_1 NOT NULL,
    FATHER_ID  BIGINT
);

CREATE TABLE VIRTUAL_FILES (
    FILE_ID               BIGINT NOT NULL,
    VIRTUAL_PATH_ID       BIGINT NOT NULL,
    PHYSICAL_FILE_ID      BIGINT NOT NULL,
    VIRTUAL_PATH_FILE_ID  BIGINT
);

CREATE TABLE VIRTUAL_PATHS (
    PATH_ID       BIGINT NOT NULL,
    PATH          VARCHAR(500) NOT NULL,
    FATHER_ID     BIGINT,
    PHYS_PATH_ID  BIGINT
);

CREATE TABLE VOLUMES (
    VOLUME_ID    BIGINT NOT NULL,
    VOLUME_NAME  VARCHAR(100) CHARACTER SET ISO8859_1 NOT NULL
);



/* Check constraints definition */

ALTER TABLE PATHS ADD CONSTRAINT CHK1_PATHS check ((FATHER_ID <> PATH_ID) OR (FATHER_ID IS NULL));
ALTER TABLE VIRTUAL_PATHS ADD CONSTRAINT CHK1_VIRTUAL_PATHS check ((FATHER_ID IS NULL) OR ( FATHER_ID <> PATH_ID));


/******************************************************************************/
/****                          Unique Constraints                          ****/
/******************************************************************************/

ALTER TABLE VOLUMES ADD CONSTRAINT UNQ_VOLUMES UNIQUE (VOLUME_NAME);


/******************************************************************************/
/****                             Primary Keys                             ****/
/******************************************************************************/

ALTER TABLE FILES ADD CONSTRAINT PK_FILES PRIMARY KEY (FILE_ID);
ALTER TABLE PATHS ADD CONSTRAINT PK_PATHS PRIMARY KEY (PATH_ID);
ALTER TABLE VIRTUAL_FILES ADD CONSTRAINT PK_VIRTUAL_FILES PRIMARY KEY (FILE_ID);
ALTER TABLE VIRTUAL_PATHS ADD CONSTRAINT PK_VIRTUAL_PATHS PRIMARY KEY (PATH_ID);
ALTER TABLE VOLUMES ADD CONSTRAINT PK_VOLUMES PRIMARY KEY (VOLUME_ID);


/******************************************************************************/
/****                             Foreign Keys                             ****/
/******************************************************************************/

ALTER TABLE FILES ADD CONSTRAINT FK_FILES_PATHS FOREIGN KEY (PATH_ID) REFERENCES PATHS (PATH_ID);
ALTER TABLE FILES ADD CONSTRAINT FK_FILES_PATHS2 FOREIGN KEY (PATH_FILE_ID) REFERENCES PATHS (PATH_ID);
ALTER TABLE PATHS ADD CONSTRAINT FK_PATHS_PATHS FOREIGN KEY (FATHER_ID) REFERENCES PATHS (PATH_ID);
ALTER TABLE PATHS ADD CONSTRAINT FK_PATHS_VOLUMES FOREIGN KEY (VOLUME_ID) REFERENCES VOLUMES (VOLUME_ID);
ALTER TABLE VIRTUAL_FILES ADD CONSTRAINT FK_VIRTUAL_FILES_FILES FOREIGN KEY (PHYSICAL_FILE_ID) REFERENCES FILES (FILE_ID);
ALTER TABLE VIRTUAL_FILES ADD CONSTRAINT FK_VIRTUAL_FILES_VIRTUAL_PATHS FOREIGN KEY (VIRTUAL_PATH_ID) REFERENCES VIRTUAL_PATHS (PATH_ID);
ALTER TABLE VIRTUAL_FILES ADD CONSTRAINT FK_VIRTUAL_FILES_VIRTUAL_PATHS2 FOREIGN KEY (VIRTUAL_PATH_FILE_ID) REFERENCES VIRTUAL_PATHS (PATH_ID);
ALTER TABLE VIRTUAL_PATHS ADD CONSTRAINT FK_VIRTUAL_PATHS_PATHS FOREIGN KEY (PHYS_PATH_ID) REFERENCES PATHS (PATH_ID);
ALTER TABLE VIRTUAL_PATHS ADD CONSTRAINT FK_VIRTUAL_PATHS_VIRTUAL_PATHS FOREIGN KEY (FATHER_ID) REFERENCES VIRTUAL_PATHS (PATH_ID);


/******************************************************************************/
/****                               Triggers                               ****/
/******************************************************************************/


SET TERM ^ ;


/******************************************************************************/
/****                         Triggers for tables                          ****/
/******************************************************************************/



/* Trigger: FILES_BI */
CREATE TRIGGER FILES_BI FOR FILES
ACTIVE BEFORE INSERT POSITION 0
AS 
BEGIN 
  IF (NEW.FILE_ID IS NULL) THEN 
    NEW.FILE_ID = GEN_ID(GEN_FILES_ID,1); 
END
^

/* Trigger: PATHS_BI */
CREATE TRIGGER PATHS_BI FOR PATHS
ACTIVE BEFORE INSERT POSITION 0
AS 
BEGIN 
  IF (NEW.PATH_ID IS NULL) THEN 
    NEW.PATH_ID = GEN_ID(GEN_PATHS_ID,1); 
END
^

/* Trigger: VIRTUAL_FILES_BI */
CREATE TRIGGER VIRTUAL_FILES_BI FOR VIRTUAL_FILES
ACTIVE BEFORE INSERT POSITION 0
AS
BEGIN
  IF (NEW.FILE_ID IS NULL) THEN
    NEW.FILE_ID = GEN_ID(GEN_VIRTUAL_FILES_ID,1);
END
^

/* Trigger: VIRTUAL_PATHS_BI */
CREATE TRIGGER VIRTUAL_PATHS_BI FOR VIRTUAL_PATHS
ACTIVE BEFORE INSERT POSITION 0
AS
BEGIN
  IF (NEW.PATH_ID IS NULL) THEN
    NEW.PATH_ID = GEN_ID(GEN_VIRTUAL_PATHS_ID,1);
END
^

/* Trigger: VOLUMES_BI */
CREATE TRIGGER VOLUMES_BI FOR VOLUMES
ACTIVE BEFORE INSERT POSITION 0
AS 
BEGIN 
  IF (NEW.VOLUME_ID IS NULL) THEN 
    NEW.VOLUME_ID = GEN_ID(GEN_VOLUMES_ID,1); 
END
^

SET TERM ; ^



/******************************************************************************/
/****                          Stored Procedures                           ****/
/******************************************************************************/


SET TERM ^ ;

ALTER PROCEDURE SP_ADD_PHYSFILE_TO_VIRTUALPATH (
    PHYS_FILE_ID BIGINT,
    VIRTUAL_PATH_ID BIGINT)
AS
begin
    if (not (exists( select FILE_ID
                   from VIRTUAL_FILES
                   where VIRTUAL_PATH_ID = :VIRTUAL_PATH_ID and PHYSICAL_FILE_ID = :PHYS_FILE_ID )))
                   then
    begin
        insert into virtual_files ( VIRTUAL_PATH_ID, PHYSICAL_FILE_ID )
        values ( :VIRTUAL_PATH_ID, :PHYS_FILE_ID );
    end
end
^

ALTER PROCEDURE SP_ADD_PHYSPATH_TO_VIRTUALPATH (
    PHYS_PATH_ID BIGINT,
    VIRTUAL_PATH_ID BIGINT)
AS
declare variable FILE_ID bigint;
declare variable PATH_ID bigint;
declare variable VPATH_ID bigint;
declare variable PATH_NAME varchar(500) character set NONE;
begin
    -- copies all files in the current folder
    for select FILE_ID
    from FILES
    where PATH_ID = :PHYS_PATH_ID
    into
        :FILE_ID
    do
    begin
        execute procedure SP_ADD_PHYSFILE_TO_VIRTUALPATH( :FILE_ID, :VIRTUAL_PATH_ID );
    end
    -- recursion in the subfolders
    for select PATH_ID, PATH_NAME
    from PATHS
    where FATHER_ID = :PHYS_PATH_ID
    into
         :PATH_ID, :PATH_NAME
    do
    begin
        -- creates the folder
        execute procedure SP_CREATE_VIRTUALPATH( :PATH_NAME, :VIRTUAL_PATH_ID, :PATH_ID, 0 )
            returning_values( :VPATH_ID );

        if( exists( select FILE_ID from VIRTUAL_FILES
                    where VIRTUAL_PATH_ID = :VIRTUAL_PATH_ID and VIRTUAL_PATH_FILE_ID = :VPATH_ID)) then
        begin
            -- there is already a file representing this folder:
            -- delete the one we have just copied to avoid a duplicate
            delete from VIRTUAL_FILES
            where FILE_ID = (select VIRTUAL_FILES.FILE_ID
                             from VIRTUAL_FILES inner join FILES on VIRTUAL_FILES.PHYSICAL_FILE_ID = FILES.FILE_ID
                             where FILES.PATH_FILE_ID = :PATH_ID);
        end
        else
        begin


            -- updates the virtual file representing this folder with a pointer to this folder
            update VIRTUAL_FILES set VIRTUAL_PATH_FILE_ID = :VPATH_ID
            where FILE_ID = (select VIRTUAL_FILES.FILE_ID
                             from VIRTUAL_FILES inner join FILES on VIRTUAL_FILES.PHYSICAL_FILE_ID = FILES.FILE_ID
                             where FILES.PATH_FILE_ID = :PATH_ID);
        end
        -- recursion
        execute procedure SP_ADD_PHYSPATH_TO_VIRTUALPATH( :PATH_ID, VPATH_ID );
    end
end
^

ALTER PROCEDURE SP_ADD_VOLUME_TO_VIRTUALPATH (
    VOLUME_ID BIGINT,
    PHYS_PATH_ID BIGINT,
    VIRTUAL_PATH_ID BIGINT)
AS
declare variable VOLUME_NAME varchar(500);
declare variable TMP_STR varchar(500);
declare variable NEW_VIRTUAL_PATH_ID bigint;
begin
    -- retrieves the name of the volume
    for select VOLUME_NAME
    from VOLUMES
    where VOLUME_ID = :VOLUME_ID
    into
        :TMP_STR
    do
    begin
        VOLUME_NAME = TMP_STR;
    end

    -- creates the new virtual folder as a child of the one received as a parameter
    execute procedure SP_CREATE_VIRTUALPATH( VOLUME_NAME, VIRTUAL_PATH_ID, NULL, 1 )
        returning_values( :NEW_VIRTUAL_PATH_ID );

    -- copies the content of the physical folder to the new virtual folder
    execute procedure SP_ADD_PHYSPATH_TO_VIRTUALPATH( PHYS_PATH_ID, NEW_VIRTUAL_PATH_ID );
end
^

ALTER PROCEDURE SP_APPEND_PHYSPTH_TO_VIRTUALPTH (
    PHYS_PATH_ID BIGINT,
    VIRTUAL_PATH_ID BIGINT)
AS
declare variable phys_path_name varchar(500) character set none;
declare variable tmp_str varchar(500);
declare variable new_virtual_path_id bigint;
begin
    -- retrieves the name of the physical folder
    for select PATH_NAME
    from PATHS
    where PATH_ID = :PHYS_PATH_ID
    into
        :TMP_STR
    do
    begin
        PHYS_PATH_NAME = TMP_STR;
    end

    -- creates the new virtual folder as a child of the one received as a parameter
    execute procedure SP_CREATE_VIRTUALPATH( PHYS_PATH_NAME, VIRTUAL_PATH_ID, PHYS_PATH_ID, 1 )
        returning_values( :NEW_VIRTUAL_PATH_ID );

    -- copies the content of the physical folder to the new virtual folder
    execute procedure SP_ADD_PHYSPATH_TO_VIRTUALPATH( PHYS_PATH_ID, NEW_VIRTUAL_PATH_ID );

end
^

ALTER PROCEDURE SP_CREATE_UNIQUE_VIRTUALPATH (
    PATH_NAME VARCHAR(500),
    FATHER_ID BIGINT,
    PHYS_PATH_ID BIGINT)
RETURNS (
    VPATH_ID BIGINT)
AS
begin
    if( exists( select PATH_ID
                from VIRTUAL_PATHS
                where FATHER_ID = :FATHER_ID and PATH = :PATH_NAME )) then
    begin
        VPATH_ID = -1;
    end
    else
    begin
        if( FATHER_ID is null ) then
        begin
            -- we are inserting a root virtual path: very simple case
            execute procedure SP_CREATE_VIRTUALPATH( :PATH_NAME, :FATHER_ID, :PHYS_PATH_ID, 0 )
            returning_values( VPATH_ID );
        end
        else
        begin
            execute procedure SP_CREATE_VIRTUALPATH( :PATH_NAME, :FATHER_ID, :PHYS_PATH_ID, 1 )
            returning_values( VPATH_ID );
        end
    end
end
^

ALTER PROCEDURE SP_CREATE_VIRTUALPATH (
    PATH_NAME VARCHAR(500),
    FATHER_ID BIGINT,
    PHYS_PATH_ID BIGINT,
    CREATE_VIRTUAL_FOLDER_FILE SMALLINT)
RETURNS (
    VPATH_ID BIGINT)
AS
declare variable tmp_id bigint;
declare variable phys_file_id bigint;
begin
    VPATH_ID = -1;   -- impossible value

    -- looks for an existing folder
    for select PATH_ID
    from VIRTUAL_PATHS
    where FATHER_ID = :FATHER_ID and PATH = :PATH_NAME
    into
        :TMP_ID
    do
    begin
        VPATH_ID = TMP_ID;
    end

    if( VPATH_ID = -1 ) then
    begin
        -- the path does not exists: we create one
        VPATH_ID = gen_id( GEN_VIRTUAL_PATHS_ID, 1 );
        insert into VIRTUAL_PATHS ( PATH_ID, PATH, FATHER_ID, PHYS_PATH_ID )
        values ( :VPATH_ID, :PATH_NAME, :FATHER_ID, :PHYS_PATH_ID );

        if( CREATE_VIRTUAL_FOLDER_FILE = 1 ) then
        begin
            -- now we need to create a row in VIRTUAL_FILES for this path:
            -- that row needs to link to a row in FILES

            if( PHYS_PATH_ID is null ) then
            begin
                -- the virtual path that we are creating does not have
                -- a corresponding physical path: we need to add a row to
                -- the FILES table because there is not one yet
                PHYS_FILE_ID = gen_id( GEN_FILES_ID, 1 );
                insert into FILES( FILE_ID, FILE_NAME, FILE_SIZE, FILE_EXT, FILE_DATETIME, PATH_ID )
                values( :PHYS_FILE_ID, :PATH_NAME, 0, '', 'NOW', NULL );
            end
            else
            begin
                -- the virtual path that we are creating has a corresponding
                -- physical path, so we look for the existing row in the FILES table
                execute procedure SP_GET_PHYS_FILEID_FROM_PATHID( :PHYS_PATH_ID )
                    returning_values( :PHYS_FILE_ID );
            end

            -- now we can insert the row
            insert into VIRTUAL_FILES( VIRTUAL_PATH_ID, PHYSICAL_FILE_ID, VIRTUAL_PATH_FILE_ID )
            values( :FATHER_ID, :PHYS_FILE_ID, :VPATH_ID );

        end
    end
end
^

ALTER PROCEDURE SP_DELETE_VIRTUAL_FOLDER (
    VIRTUAL_PATH_ID BIGINT)
AS
declare variable PATH_ID bigint;
declare variable TMP_ID bigint;
declare variable FILE_ID bigint;
begin
    for select PATH_ID
    from VIRTUAL_PATHS
    where FATHER_ID = :VIRTUAL_PATH_ID
    into
        :PATH_ID
    do
    begin
        -- recurse to delete all che children of this path to avoid problems
        -- with referential integrity
        execute procedure SP_DELETE_VIRTUAL_FOLDER( :PATH_ID );
    end

    -- now delete the FILES row corresponding to this virtual path
    -- (only if this path has been created by the user, so it has no
    --  corresponding physical path)
    -- we cannot delete now because we would break a foreign key,
    --  so we store the key of the row to be deleted
    FILE_ID = -1;
    for select FILES.FILE_ID
    from FILES inner join VIRTUAL_FILES
    on FILES.FILE_ID = VIRTUAL_FILES.PHYSICAL_FILE_ID
    where FILES.PATH_ID is null and VIRTUAL_FILES.VIRTUAL_PATH_FILE_ID = :VIRTUAL_PATH_ID
    into :TMP_ID
    do
    begin
        FILE_ID = TMP_ID;
    end

    -- now delete all the virtual files of this folder
    delete from VIRTUAL_FILES where VIRTUAL_PATH_ID = :VIRTUAL_PATH_ID;

    -- delete the VIRTUAL_FILES row that describes this path
    delete from VIRTUAL_FILES where VIRTUAL_PATH_FILE_ID = :VIRTUAL_PATH_ID;

    -- now delete the virtual folder received as a parameter
    delete from VIRTUAL_PATHS where PATH_ID = :VIRTUAL_PATH_ID;

    -- finally delete the FILES row, if any
    if( :FILE_ID > 0 ) then
    begin
        delete from FILES where FILE_ID = :FILE_ID;
    end

end
^

ALTER PROCEDURE SP_DELETE_VOLUME (
    VOLUME_ID BIGINT)
AS
declare variable PATH_ID bigint;
begin
  /* reads all the paths for the given volume in descending order
     to avoid problem with referential integrity: it deletes first
     rows inserted last */
  for select PATH_ID
      from PATHS
      where VOLUME_ID = :VOLUME_ID
      order by PATH_ID desc
  into
      :PATH_ID
  do
  begin
      delete from FILES where PATH_ID = :PATH_ID;
      delete from FILES where PATH_FILE_ID = :PATH_ID;
      delete from PATHS where PATH_ID = :PATH_ID;
  end
  delete from VOLUMES where VOLUME_ID = :VOLUME_ID;
end
^

ALTER PROCEDURE SP_GET_FULL_PATH (
    PHYS_PATH_ID BIGINT,
    PATH_SEPARATOR VARCHAR(5))
RETURNS (
    FULL_PATH VARCHAR(500))
AS
declare variable TMP_ID bigint;
declare variable FATH_ID bigint;
declare variable TMP_VOL_NAME varchar(500);
declare variable VOL_NAME varchar(500);
declare variable TMP_PATH_NAME varchar(500);
declare variable PATH_NAME varchar(500);
begin
      -- looks for the father ID and the volume name
      for select PATHS.FATHER_ID, PATHS.PATH_NAME, VOLUMES.VOLUME_NAME
      from PATHS inner join VOLUMES
      on PATHS.VOLUME_ID = VOLUMES.VOLUME_ID
      where PATHS.PATH_ID = :PHYS_PATH_ID
      into
        :TMP_ID, :TMP_PATH_NAME, :TMP_VOL_NAME
      do
      begin
        FATH_ID = TMP_ID;
        VOL_NAME = TMP_VOL_NAME;
        PATH_NAME = TMP_PATH_NAME;
      end

      if( FATH_ID is null ) then
      begin
        -- this is the root path, return the volume name
        FULL_PATH = VOL_NAME;
      end
      else
      begin
        -- recursion into the father folder
        execute procedure SP_GET_FULL_PATH( :FATH_ID, :PATH_SEPARATOR )
          returning_values( :TMP_PATH_NAME );
        FULL_PATH = TMP_PATH_NAME || PATH_SEPARATOR || PATH_NAME;
      end
end
^

ALTER PROCEDURE SP_GET_PHYS_FILEID_FROM_PATHID (
    PATH_ID BIGINT)
RETURNS (
    FILE_ID BIGINT)
AS
declare variable tmp_id bigint;
begin
    FILE_ID = -1;

    for select FILE_ID
    from FILES
    where PATH_FILE_ID = :PATH_ID
    into
        :TMP_ID
    do
        FILE_ID = TMP_ID;
end
^

ALTER PROCEDURE SP_RENAME_VIRTUALPATH (
    VPATH_ID BIGINT,
    PATH_NAME VARCHAR(500))
RETURNS (
    STATUS INTEGER)
AS
declare variable father_id bigint;
declare variable physical_path_id bigint;
declare variable tmp_id bigint;
declare variable tmp_id2 bigint;
begin
    STATUS = 0;

     -- looks for the father id
    for select FATHER_ID, PHYS_PATH_ID
    from VIRTUAL_PATHS
    where PATH_ID = :VPATH_ID
    into
        :TMP_ID, :TMP_ID2
    do
    begin
        FATHER_ID = TMP_ID;
        PHYSICAL_PATH_ID = TMP_ID2;
    end

    -- do not rename physical paths
    if( not PHYSICAL_PATH_ID is null ) then exception EX_RENAME_PHYSICAL_PATH;

    -- avoids duplicates paths
    if( exists( select PATH_ID from VIRTUAL_PATHS where FATHER_ID = :FATHER_ID and PATH = :PATH_NAME )) then
    begin
        STATUS = -1;
        exit;
    end

    -- here if we can rename
    update VIRTUAL_PATHS set PATH = :PATH_NAME where PATH_ID = :VPATH_ID;
    update FILES set FILE_NAME = :PATH_NAME where FILE_ID =
    (select PHYSICAL_FILE_ID
     from VIRTUAL_FILES
     where VIRTUAL_PATH_FILE_ID = :VPATH_ID);

end
^


SET TERM ; ^


/******************************************************************************/
/****                             Descriptions                             ****/
/******************************************************************************/

DESCRIBE TABLE VIRTUAL_PATHS
'Stores the folders structure for the virtual view';



/******************************************************************************/
/****                             Descriptions                             ****/
/******************************************************************************/

DESCRIBE PROCEDURE SP_ADD_PHYSPATH_TO_VIRTUALPATH
'Assigns the contents of the physical path to then virtual path.
It will not create duplicate files or folders.';

DESCRIBE PROCEDURE SP_APPEND_PHYSPTH_TO_VIRTUALPTH
'Appends the physical folder and its contents to a child of the virtual folder.
It will create a virtual folder, child of the specified virtual folder,
with the same name as the physical folder.';

DESCRIBE PROCEDURE SP_CREATE_UNIQUE_VIRTUALPATH
'Returns -1 if then pathname is already present in the database';

DESCRIBE PROCEDURE SP_CREATE_VIRTUALPATH
'If there is not a virtual folder with the specied name creates that folder
and returns its primary key.
If the folder already exists return its primary key.
The procedure will allow only one path with a given name to be the child of
another path. The value of PHYS_PATH_ID does not matter.';

DESCRIBE PROCEDURE SP_GET_FULL_PATH
'Returns the full path of a given PATH_ID.';

DESCRIBE PROCEDURE SP_GET_PHYS_FILEID_FROM_PATHID
'Returns FILES.FILE_ID of the row corresponding to the value of
PATHS.PATH_ID received as a parameter';

DESCRIBE PROCEDURE SP_RENAME_VIRTUALPATH
'Changes the name of a virtual folder created by the user: no link to physical path.';



/* Fields descriptions */

DESCRIBE FIELD PATH_ID TABLE FILES
'If PATH_ID is null this row represents a virtual folder created by the user.';

DESCRIBE FIELD PATH_FILE_ID TABLE FILES
'This field is NULL if the row represents a file.
It is not NULL if the row represents a path (folder) and it contains the primary key of the PATHS row that it is describing.';

DESCRIBE FIELD FATHER_ID TABLE PATHS
'ID of the path of the father folder, NULL if none';

DESCRIBE FIELD VIRTUAL_PATH_FILE_ID TABLE VIRTUAL_FILES
'This field is NULL if the row represents a file.
It is not NULL if the row represents a virtual path (folder) and it contains the primary key of the VIRTUAL_PATHS row that it is describing.';

DESCRIBE FIELD PHYS_PATH_ID TABLE VIRTUAL_PATHS
'Points the corresponding real folder, if there is one.
If this is a virtual path created by the user it is NULL.';



/* Parameters descriptions */

DESCRIBE PARAMETER PHYS_FILE_ID PROCEDURE SP_ADD_PHYSFILE_TO_VIRTUALPATH
'FILES.FILE_ID of the file to be added';

DESCRIBE PARAMETER VIRTUAL_PATH_ID PROCEDURE SP_ADD_PHYSFILE_TO_VIRTUALPATH
'Primary key of the virtual folder that will receive the file';

DESCRIBE PARAMETER VPATH_ID PROCEDURE SP_CREATE_UNIQUE_VIRTUALPATH
'The SP returns -1 if the folder name is already present';

DESCRIBE PARAMETER CREATE_VIRTUAL_FOLDER_FILE PROCEDURE SP_CREATE_VIRTUALPATH
'If = 1 it also creates a virtual file corresponding to the created virtual folder.';

DESCRIBE PARAMETER STATUS PROCEDURE SP_RENAME_VIRTUALPATH
'0=OK, -1=error: new name would be duplicated';

