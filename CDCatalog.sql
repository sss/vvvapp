/* Please note that this script doesn't maintain
   proper order of creation for computed columns if
   they reference other tables.  */

/********************* ROLES **********************/

/********************* UDFS ***********************/

/****************** GENERATORS ********************/

CREATE GENERATOR GEN_FILES_ID;
CREATE GENERATOR GEN_PATHS_ID;
CREATE GENERATOR GEN_VIRTUAL_FILES_ID;
CREATE GENERATOR GEN_VIRTUAL_PATHS_ID;
CREATE GENERATOR GEN_VOLUMES_ID;
/******************** DOMAINS *********************/

/******************* PROCEDURES ******************/

SET TERM ^ ;
CREATE PROCEDURE SP_ADD_PHYSFILE_TO_VIRTUALPATH (
    PHYS_FILE_ID Numeric(18,0),
    VIRTUAL_PATH_ID Numeric(18,0) )
AS
BEGIN EXIT; END^
SET TERM ; ^

SET TERM ^ ;
CREATE PROCEDURE SP_ADD_PHYSPATH_TO_VIRTUALPATH (
    PHYS_PATH_ID Numeric(18,0),
    VIRTUAL_PATH_ID Numeric(18,0) )
AS
BEGIN EXIT; END^
SET TERM ; ^

SET TERM ^ ;
CREATE PROCEDURE SP_APPEND_PHYSPTH_TO_VIRTUALPTH (
    PHYS_PATH_ID Numeric(18,0),
    VIRTUAL_PATH_ID Numeric(18,0) )
AS
BEGIN EXIT; END^
SET TERM ; ^

SET TERM ^ ;
CREATE PROCEDURE SP_CREATE_UNIQUE_VIRTUALPATH (
    PATH_NAME Varchar(500),
    FATHER_ID Numeric(18,0),
    PHYS_PATH_ID Numeric(18,0) )
RETURNS (
    VPATH_ID Numeric(18,0) )
AS
BEGIN EXIT; END^
SET TERM ; ^

SET TERM ^ ;
CREATE PROCEDURE SP_CREATE_VIRTUALPATH (
    PATH_NAME Varchar(500),
    FATHER_ID Numeric(18,0),
    PHYS_PATH_ID Numeric(18,0),
    CREATE_VIRTUAL_FOLDER_FILE Smallint )
RETURNS (
    VPATH_ID Numeric(18,0) )
AS
BEGIN EXIT; END^
SET TERM ; ^

SET TERM ^ ;
CREATE PROCEDURE SP_DELETE_VIRTUAL_FOLDER (
    VIRTUAL_PATH_ID Numeric(18,0) )
AS
BEGIN EXIT; END^
SET TERM ; ^

SET TERM ^ ;
CREATE PROCEDURE SP_DELETE_VOLUME (
    VOLUME_ID Numeric(18,0) )
AS
BEGIN EXIT; END^
SET TERM ; ^

SET TERM ^ ;
CREATE PROCEDURE SP_GET_PHYS_FILEID_FROM_PATHID (
    PATH_ID Numeric(18,0) )
RETURNS (
    FILE_ID Numeric(18,0) )
AS
BEGIN EXIT; END^
SET TERM ; ^

/******************** TABLES **********************/

CREATE TABLE FILES
(
  FILE_ID Numeric(18,0) NOT NULL,
  FILE_NAME Varchar(500) CHARACTER SET ISO8859_1,
  FILE_SIZE Numeric(18,0),
  FILE_EXT Varchar(50) CHARACTER SET ISO8859_1,
  FILE_DATETIME Timestamp,
  PATH_ID Numeric(18,0),
  IS_FOLDER Char(1),
  CONSTRAINT PK_FILES PRIMARY KEY (FILE_ID)
);
CREATE TABLE PATHS
(
  PATH_ID Numeric(18,0) NOT NULL,
  VOLUME_ID Numeric(18,0) NOT NULL,
  PATH_NAME Varchar(500) CHARACTER SET ISO8859_1 NOT NULL,
  FATHER_ID Numeric(18,0),
  CONSTRAINT PK_PATHS PRIMARY KEY (PATH_ID)
);
CREATE TABLE VIRTUAL_FILES
(
  FILE_ID Numeric(18,0) NOT NULL,
  VIRTUAL_PATH_ID Numeric(18,0) NOT NULL,
  PHYSICAL_FILE_ID Numeric(18,0) NOT NULL,
  CONSTRAINT PK_VIRTUAL_FILES PRIMARY KEY (FILE_ID)
);
CREATE TABLE VIRTUAL_PATHS
(
  PATH_ID Numeric(18,0) NOT NULL,
  PATH Varchar(500) NOT NULL,
  FATHER_ID Numeric(18,0),
  PHYS_PATH_ID Numeric(18,0),
  CONSTRAINT PK_VIRTUAL_PATHS PRIMARY KEY (PATH_ID)
);
CREATE TABLE VOLUMES
(
  VOLUME_ID Numeric(18,0) NOT NULL,
  VOLUME_NAME Varchar(100) CHARACTER SET ISO8859_1 NOT NULL,
  CONSTRAINT PK_VOLUMES PRIMARY KEY (VOLUME_ID),
  CONSTRAINT UNQ_VOLUMES UNIQUE (VOLUME_NAME)
);
/********************* VIEWS **********************/

/******************* EXCEPTIONS *******************/

/******************** TRIGGERS ********************/

SET TERM ^ ;
CREATE TRIGGER FILES_BI FOR FILES ACTIVE
BEFORE INSERT POSITION 0
AS 
BEGIN 
  IF (NEW.FILE_ID IS NULL) THEN 
    NEW.FILE_ID = GEN_ID(GEN_FILES_ID,1); 
END^
SET TERM ; ^
SET TERM ^ ;
CREATE TRIGGER PATHS_BI FOR PATHS ACTIVE
BEFORE INSERT POSITION 0
AS 
BEGIN 
  IF (NEW.PATH_ID IS NULL) THEN 
    NEW.PATH_ID = GEN_ID(GEN_PATHS_ID,1); 
END^
SET TERM ; ^
SET TERM ^ ;
CREATE TRIGGER VIRTUAL_FILES_BI FOR VIRTUAL_FILES ACTIVE
BEFORE INSERT POSITION 0
AS
BEGIN
  IF (NEW.FILE_ID IS NULL) THEN
    NEW.FILE_ID = GEN_ID(GEN_VIRTUAL_FILES_ID,1);
END^
SET TERM ; ^
SET TERM ^ ;
CREATE TRIGGER VIRTUAL_PATHS_BI FOR VIRTUAL_PATHS ACTIVE
BEFORE INSERT POSITION 0
AS
BEGIN
  IF (NEW.PATH_ID IS NULL) THEN
    NEW.PATH_ID = GEN_ID(GEN_VIRTUAL_PATHS_ID,1);
END^
SET TERM ; ^
SET TERM ^ ;
CREATE TRIGGER VOLUMES_BI FOR VOLUMES ACTIVE
BEFORE INSERT POSITION 0
AS 
BEGIN 
  IF (NEW.VOLUME_ID IS NULL) THEN 
    NEW.VOLUME_ID = GEN_ID(GEN_VOLUMES_ID,1); 
END^
SET TERM ; ^

SET TERM ^ ;
ALTER PROCEDURE SP_ADD_PHYSFILE_TO_VIRTUALPATH (
    PHYS_FILE_ID Numeric(18,0),
    VIRTUAL_PATH_ID Numeric(18,0) )
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
end^
SET TERM ; ^

GRANT EXECUTE
 ON PROCEDURE SP_ADD_PHYSFILE_TO_VIRTUALPATH TO  SYSDBA;

UPDATE RDB$PROCEDURE_PARAMETERS set RDB$DESCRIPTION = 'FILES.FILE_ID of the file to be added'
  where RDB$PARAMETER_NAME = 'PHYS_FILE_ID' AND RDB$PROCEDURE_NAME = 'SP_ADD_PHYSFILE_TO_VIRTUALPATH';
UPDATE RDB$PROCEDURE_PARAMETERS set RDB$DESCRIPTION = 'Primary key of the virtual folder that will receive the file'
  where RDB$PARAMETER_NAME = 'VIRTUAL_PATH_ID' AND RDB$PROCEDURE_NAME = 'SP_ADD_PHYSFILE_TO_VIRTUALPATH';

SET TERM ^ ;
ALTER PROCEDURE SP_ADD_PHYSPATH_TO_VIRTUALPATH (
    PHYS_PATH_ID Numeric(18,0),
    VIRTUAL_PATH_ID Numeric(18,0) )
AS
declare variable file_id bigint;
declare variable path_id bigint;
declare variable vpath_id bigint;
declare variable path_name varchar(500) character set none;
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
        execute procedure SP_CREATE_VIRTUALPATH( :PATH_NAME, :VIRTUAL_PATH_ID, :PATH_ID, 0 )
            returning_values( :VPATH_ID );
--        VPATH_ID = gen_id( GEN_VIRTUAL_PATHS_ID, 1 );
--        insert into VIRTUAL_PATHS ( PATH_ID, PATH, FATHER_ID, PHYS_PATH_ID )
--        values ( :VPATH_ID, :PATH_NAME, :VIRTUAL_PATH_ID, :PATH_ID );
        execute procedure SP_ADD_PHYSPATH_TO_VIRTUALPATH( :PATH_ID, VPATH_ID );
    end
end^
SET TERM ; ^

GRANT EXECUTE
 ON PROCEDURE SP_ADD_PHYSPATH_TO_VIRTUALPATH TO  SYSDBA;

UPDATE RDB$PROCEDURES set
  RDB$DESCRIPTION = 'Assigns the contents of the physical path to then virtual path.
It will not create duplicate files or folders.'
  where RDB$PROCEDURE_NAME = 'SP_ADD_PHYSPATH_TO_VIRTUALPATH';

SET TERM ^ ;
ALTER PROCEDURE SP_APPEND_PHYSPTH_TO_VIRTUALPTH (
    PHYS_PATH_ID Numeric(18,0),
    VIRTUAL_PATH_ID Numeric(18,0) )
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

end^
SET TERM ; ^

GRANT EXECUTE
 ON PROCEDURE SP_APPEND_PHYSPTH_TO_VIRTUALPTH TO  SYSDBA;

UPDATE RDB$PROCEDURES set
  RDB$DESCRIPTION = 'Appends the physical folder and its contents to a child of the virtual folder.
It will create a virtual folder, child of the specified virtual folder,
with the same name as the physical folder.'
  where RDB$PROCEDURE_NAME = 'SP_APPEND_PHYSPTH_TO_VIRTUALPTH';

SET TERM ^ ;
ALTER PROCEDURE SP_CREATE_UNIQUE_VIRTUALPATH (
    PATH_NAME Varchar(500),
    FATHER_ID Numeric(18,0),
    PHYS_PATH_ID Numeric(18,0) )
RETURNS (
    VPATH_ID Numeric(18,0) )
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
        execute procedure SP_CREATE_VIRTUALPATH( :PATH_NAME, :FATHER_ID, :PHYS_PATH_ID, 1 )
        returning_values( VPATH_ID );
    end
end^
SET TERM ; ^

GRANT EXECUTE
 ON PROCEDURE SP_CREATE_UNIQUE_VIRTUALPATH TO  SYSDBA;

UPDATE RDB$PROCEDURE_PARAMETERS set RDB$DESCRIPTION = 'The SP returns -1 if the folder name is already present'
  where RDB$PARAMETER_NAME = 'VPATH_ID' AND RDB$PROCEDURE_NAME = 'SP_CREATE_UNIQUE_VIRTUALPATH';

SET TERM ^ ;
ALTER PROCEDURE SP_CREATE_VIRTUALPATH (
    PATH_NAME Varchar(500),
    FATHER_ID Numeric(18,0),
    PHYS_PATH_ID Numeric(18,0),
    CREATE_VIRTUAL_FOLDER_FILE Smallint )
RETURNS (
    VPATH_ID Numeric(18,0) )
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
                insert into FILES( FILE_ID, FILE_NAME, FILE_EXT, FILE_DATETIME, PATH_ID, IS_FOLDER )
                values( :PHYS_FILE_ID, :PATH_NAME, '', 'NOW', NULL, 'T' );
            end
            else
            begin
                -- the virtual path that we are creating has a corresponding
                -- physical path, so we look fot the existing row in the FILES table
                execute procedure SP_GET_PHYS_FILEID_FROM_PATHID( :PHYS_PATH_ID )
                    returning_values( :PHYS_FILE_ID );
            end

            -- now we can insert the row
            insert into VIRTUAL_FILES( VIRTUAL_PATH_ID, PHYSICAL_FILE_ID )
            values( :FATHER_ID, :PHYS_FILE_ID );

        end
    end
end^
SET TERM ; ^

GRANT EXECUTE
 ON PROCEDURE SP_CREATE_VIRTUALPATH TO  SYSDBA;

UPDATE RDB$PROCEDURES set
  RDB$DESCRIPTION = 'If there is not a virtual folder with the specied name creates that folder
and returns its primary key.
If the folder already exists return its primary key.
The procedure will allow only one path with a given name to be the child of
another path. The value of PHYS_PATH_ID does not matter.'
  where RDB$PROCEDURE_NAME = 'SP_CREATE_VIRTUALPATH';
UPDATE RDB$PROCEDURE_PARAMETERS set RDB$DESCRIPTION = 'If = 1 it also creates a virtual file corresponding to the created virtual folder.'
  where RDB$PARAMETER_NAME = 'CREATE_VIRTUAL_FOLDER_FILE' AND RDB$PROCEDURE_NAME = 'SP_CREATE_VIRTUALPATH';

SET TERM ^ ;
ALTER PROCEDURE SP_DELETE_VIRTUAL_FOLDER (
    VIRTUAL_PATH_ID Numeric(18,0) )
AS
declare variable path_id bigint;
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

    -- now delete all the virtual files of this folder
    delete from VIRTUAL_FILES where VIRTUAL_PATH_ID = :VIRTUAL_PATH_ID;

    -- now delete the virtual folder received as a parameter
    delete from VIRTUAL_PATHS where PATH_ID = :VIRTUAL_PATH_ID;

end^
SET TERM ; ^

GRANT EXECUTE
 ON PROCEDURE SP_DELETE_VIRTUAL_FOLDER TO  SYSDBA;


SET TERM ^ ;
ALTER PROCEDURE SP_DELETE_VOLUME (
    VOLUME_ID Numeric(18,0) )
AS
declare variable path_id bigint;
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
      delete from PATHS where PATH_ID = :PATH_ID;
  end
  delete from VOLUMES where VOLUME_ID = :VOLUME_ID;
end^
SET TERM ; ^

GRANT EXECUTE
 ON PROCEDURE SP_DELETE_VOLUME TO  SYSDBA;


SET TERM ^ ;
ALTER PROCEDURE SP_GET_PHYS_FILEID_FROM_PATHID (
    PATH_ID Numeric(18,0) )
RETURNS (
    FILE_ID Numeric(18,0) )
AS
declare variable tmp_id bigint;
declare variable father_id bigint;
declare variable path_name varchar(500);
declare variable tmp_str varchar(500);
begin
    FILE_ID = -1;

    -- looks for the path name and the ID of the parent path
    for select FATHER_ID, PATH_NAME
    from PATHS
    where PATH_ID = :PATH_ID
    into
        :TMP_ID, :TMP_STR
    do
    begin
        FATHER_ID = TMP_ID;
        PATH_NAME = TMP_STR;
    end

    -- looks for the file
    for select FILE_ID
    from FILES
    where PATH_ID = :FATHER_ID and FILE_NAME = :PATH_NAME
    into
        :TMP_ID
    do
        FILE_ID = TMP_ID;
end^
SET TERM ; ^

GRANT EXECUTE
 ON PROCEDURE SP_GET_PHYS_FILEID_FROM_PATHID TO  SYSDBA;

UPDATE RDB$PROCEDURES set
  RDB$DESCRIPTION = 'Returns FILES.FILE_ID of the row corresponding to the value of
PATHS.PATH_ID received as a parameter'
  where RDB$PROCEDURE_NAME = 'SP_GET_PHYS_FILEID_FROM_PATHID';

UPDATE RDB$RELATION_FIELDS set RDB$DESCRIPTION = 'If PATH_ID is null this row represents a virtual folder created by the user.'  where RDB$FIELD_NAME = 'PATH_ID' and RDB$RELATION_NAME = 'FILES';
ALTER TABLE FILES ADD CONSTRAINT FK_FILES_PATHS
  FOREIGN KEY (PATH_ID) REFERENCES PATHS (PATH_ID);
GRANT DELETE, INSERT, REFERENCES, SELECT, UPDATE
 ON FILES TO  SYSDBA WITH GRANT OPTION;

UPDATE RDB$RELATION_FIELDS set RDB$DESCRIPTION = 'ID of the path of the father folder, NULL if none'  where RDB$FIELD_NAME = 'FATHER_ID' and RDB$RELATION_NAME = 'PATHS';
ALTER TABLE PATHS ADD CONSTRAINT FK_PATHS_PATHS
  FOREIGN KEY (FATHER_ID) REFERENCES PATHS (PATH_ID);
ALTER TABLE PATHS ADD CONSTRAINT FK_PATHS_VOLUMES
  FOREIGN KEY (VOLUME_ID) REFERENCES VOLUMES (VOLUME_ID);
ALTER TABLE PATHS ADD CONSTRAINT CHK1_PATHS
  check ((FATHER_ID <> PATH_ID) OR (FATHER_ID IS NULL));
GRANT DELETE, INSERT, REFERENCES, SELECT, UPDATE
 ON PATHS TO  SYSDBA WITH GRANT OPTION;

ALTER TABLE VIRTUAL_FILES ADD CONSTRAINT FK_VIRTUAL_FILES_FILES
  FOREIGN KEY (PHYSICAL_FILE_ID) REFERENCES FILES (FILE_ID);
ALTER TABLE VIRTUAL_FILES ADD CONSTRAINT FK_VIRTUAL_FILES_VIRTUAL_PATHS
  FOREIGN KEY (VIRTUAL_PATH_ID) REFERENCES VIRTUAL_PATHS (PATH_ID);
GRANT DELETE, INSERT, REFERENCES, SELECT, UPDATE
 ON VIRTUAL_FILES TO  SYSDBA WITH GRANT OPTION;

UPDATE RDB$RELATION_FIELDS set RDB$DESCRIPTION = 'Points the corresponding real folder, if there is one.
If this is a virtual path created by the user it is NULL.'  where RDB$FIELD_NAME = 'PHYS_PATH_ID' and RDB$RELATION_NAME = 'VIRTUAL_PATHS';
ALTER TABLE VIRTUAL_PATHS ADD CONSTRAINT FK_VIRTUAL_PATHS_PATHS
  FOREIGN KEY (PHYS_PATH_ID) REFERENCES PATHS (PATH_ID);
ALTER TABLE VIRTUAL_PATHS ADD CONSTRAINT FK_VIRTUAL_PATHS_VIRTUAL_PATHS
  FOREIGN KEY (FATHER_ID) REFERENCES VIRTUAL_PATHS (PATH_ID);
ALTER TABLE VIRTUAL_PATHS ADD CONSTRAINT CHK1_VIRTUAL_PATHS
  check ((FATHER_ID IS NULL) OR ( FATHER_ID <> PATH_ID));
GRANT DELETE, INSERT, REFERENCES, SELECT, UPDATE
 ON VIRTUAL_PATHS TO  SYSDBA WITH GRANT OPTION;

UPDATE RDB$RELATIONS set
RDB$DESCRIPTION = 'Stores the folders structure for the virtual view'
where RDB$RELATION_NAME = 'VIRTUAL_PATHS';
GRANT DELETE, INSERT, REFERENCES, SELECT, UPDATE
 ON VOLUMES TO  SYSDBA WITH GRANT OPTION;

