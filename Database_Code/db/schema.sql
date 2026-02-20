CREATE EXTENSION IF NOT EXISTS "pgcrypto";

CREATE TABLE scan (
  ScanId uuid NOT NULL PRIMARY KEY DEFAULT gen_random_uuid(),
  CardId VARCHAR(8) NOT NULL,
  FirstName VARCHAR(50),
  LastName VARCHAR(50),
  ScanDate DATE NOT NULL,
  ScanTime TIME NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_scan_cardid ON scan (CardId);