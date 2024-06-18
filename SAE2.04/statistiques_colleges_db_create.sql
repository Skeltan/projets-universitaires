DROP SCHEMA IF EXISTS colleges CASCADE;
CREATE SCHEMA colleges;


CREATE TABLE colleges._region (
    code_region VARCHAR(2) NOT NULL,
    libelle_region VARCHAR(30) NOT NULL,
    CONSTRAINT pk_region PRIMARY KEY (code_region),
    CONSTRAINT uq_region UNIQUE (libelle_region)
);

CREATE TABLE colleges._academie (
    code_academie INT NOT NULL,
    lib_academie VARCHAR(30) NOT NULL,
    CONSTRAINT pk_academie PRIMARY KEY (code_academie),
    CONSTRAINT uq_academie UNIQUE (lib_academie)
);

CREATE TABLE colleges._departement (
    code_du_departement VARCHAR(2) NOT NULL,
    nom_departement VARCHAR(30) NOT NULL,
    code_region VARCHAR(2) NOT NULL,
    CONSTRAINT pk_departement PRIMARY KEY (code_du_departement),
    CONSTRAINT uq_departement UNIQUE (nom_departement),
    CONSTRAINT fk_departement FOREIGN KEY (code_region) REFERENCES colleges._region(code_region)
);

CREATE TABLE colleges._commune (
    code_insee_de_la_commune VARCHAR(5) NOT NULL,
    nom_de_la_commune VARCHAR(50) NOT NULL,
    code_du_departement VARCHAR(2) NOT NULL,
    CONSTRAINT pk_commune PRIMARY KEY (code_insee_de_la_commune),
    CONSTRAINT uq_commune UNIQUE (nom_de_la_commune),
    CONSTRAINT fk_commune FOREIGN KEY (code_du_departement) REFERENCES colleges._departement(code_du_departement)
);

CREATE TABLE colleges._quartier_prioritaire (
    code_quartier_prioritaire VARCHAR(8) NOT NULL,
    nom_quartier_prioritaire VARCHAR(30) NOT NULL,
    CONSTRAINT pk_quartier_prioritaire PRIMARY KEY (code_quartier_prioritaire)
);

CREATE TABLE colleges._type (
    code_nature VARCHAR(3) NOT NULL,
    libelle_nature VARCHAR(30) NOT NULL,
    CONSTRAINT pk_type PRIMARY KEY (code_nature, libelle_nature)
);

CREATE TABLE colleges._etablissement (
    uai VARCHAR(8) NOT NULL,
    nom_etablissement VARCHAR(50) NOT NULL,
    secteur VARCHAR(6) NOT NULL,
    code_postal VARCHAR(5) NOT NULL,
    latitude FLOAT NOT NULL,
    longitude FLOAT NOT NULL,
    code_academie INT NOT NULL,
    code_nature VARCHAR(3) NOT NULL,
    libelle_nature VARCHAR(30) NOT NULL,
    code_quartier_prioritaire VARCHAR(8) NOT NULL,
    CONSTRAINT pk_etablissement PRIMARY KEY (uai),
    CONSTRAINT fk1_etablissement FOREIGN KEY (code_academie) REFERENCES colleges._academie(code_academie),
    CONSTRAINT fk2_etablissement FOREIGN KEY (code_nature, libelle_nature) REFERENCES colleges._type(code_nature,libelle_nature),
    CONSTRAINT fk3_etablissement FOREIGN KEY (code_quartier_prioritaire) REFERENCES colleges._quartier_prioritaire(code_quartier_prioritaire)
);

CREATE TABLE colleges._annee (
    annee_scolaire VARCHAR(9) NOT NULL,
    CONSTRAINT pk_annee PRIMARY KEY (annee_scolaire)
);

CREATE TABLE colleges._classe (
    id_classe VARCHAR(10) NOT NULL,
    CONSTRAINT pk_classe PRIMARY KEY (id_classe)
);

CREATE TABLE colleges._caracteristiques_tout_etablissement (
    uai VARCHAR(8) NOT NULL,
    annee_scolaire VARCHAR(9) NOT NULL,
    effectifs INT NOT NULL,
    ips FLOAT NOT NULL,
    ecart_type_de_l_ips FLOAT NOT NULL,
    ep VARCHAR(10) NOT NULL,
    CONSTRAINT pk_caracteristiques_tout_etablissement PRIMARY KEY (uai, annee_scolaire),
    CONSTRAINT fk1_caracteristiques_tout_etablissement FOREIGN KEY (uai) REFERENCES colleges._etablissement(uai),
    CONSTRAINT fk2_caracteristiques_tout_etablissement FOREIGN KEY (annee_scolaire) REFERENCES colleges._annee(annee_scolaire)
);

CREATE TABLE colleges._caracteristiques_college (
    uai VARCHAR(8) NOT NULL,
    annee_scolaire VARCHAR(9) NOT NULL,
    nbre_eleves_hors_segpa_hors_ulis INT NOT NULL,
    nbre_eleves_segpa INT NOT NULL,
    nbre_eleves_ulis INT NOT NULL,
    CONSTRAINT pk_caracteristiques_college PRIMARY KEY (uai, annee_scolaire),
    CONSTRAINT fk1_caracteristiques_college FOREIGN KEY (uai) REFERENCES colleges._etablissement(uai),
    CONSTRAINT fk2_caracteristiques_college FOREIGN KEY (annee_scolaire) REFERENCES colleges._annee(annee_scolaire)
);

CREATE TABLE colleges._caracteristiques_selon_classe (
    id_classe VARCHAR(10) NOT NULL,
    annee_scolaire VARCHAR(9) NOT NULL,
    nbre_eleves_hors_segpa_hors_ulis_selon_niveau INT NOT NULL,
    nbre_eleves_segpa_selon_niveau INT NOT NULL,
    nbre_eleves_ulis_selon_niveau INT NOT NULL,
    effectif_filles INT NOT NULL,
    effectif_garcons INT NOT NULL,
    CONSTRAINT pk_caracteristiques_selon_classe PRIMARY KEY (id_classe, annee_scolaire),
    CONSTRAINT fk1_caracteristiques_selon_classe FOREIGN KEY (id_classe) REFERENCES colleges._classe(id_classe),
    CONSTRAINT fk2_caracteristiques_selon_classe FOREIGN KEY (annee_scolaire) REFERENCES colleges._annee(annee_scolaire)
);

CREATE TABLE colleges._etablissement_proximite (
    uai1 VARCHAR(8) NOT NULL,
    uai2 VARCHAR(8) NOT NULL,
    CONSTRAINT pk_etablissement_proximite PRIMARY KEY (uai1, uai2),
    CONSTRAINT fk1_etablissement_proximite FOREIGN KEY (uai1) REFERENCES colleges._etablissement(uai),
    CONSTRAINT fk2_etablissement_proximite FOREIGN KEY (uai2) REFERENCES colleges._etablissement(uai)
);