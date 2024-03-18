drop schema if exists pn cascade;
create schema pn;
set schema 'pn';


CREATE TABLE competences (
    lib_competence VARCHAR(50) NOT NULL,
    CONSTRAINT competences_pk PRIMARY KEY(lib_competence)
);

CREATE TABLE parcours (
    code_P VARCHAR(1) NOT NULL,
    libelle_parcours VARCHAR(50) NOT NULL,
    nbre_gpe_TD_P INT NOT NULL,
    nbre_gpe_TP_P INT NOT NULL,
    CONSTRAINT parcours_pk PRIMARY KEY(code_P)
);

CREATE TABLE activites (
    lib_activite VARCHAR(50) NOT NULL,
    lib_competence VARCHAR(50) NOT NULL,
    CONSTRAINT activites_pk PRIMARY KEY(lib_activite),
    CONSTRAINT activites_fk FOREIGN KEY(lib_competence) references competences(lib_competence)
);


CREATE TABLE niveau (
    numero_N INT NOT NULL,
    CONSTRAINT niveau_pk PRIMARY KEY(numero_N),
    CHECK COUNT(SELECT numero_sem from semestre) <= 2
);

CREATE TABLE correspond (
    lib_activite VARCHAR(50),
    numero_N VARCHAR(50),
    code_P VARCHAR(50),
    CONSTRAINT correspond_pk PRIMARY KEY(lib_activite,numero_N,code_P),
    CONSTRAINT correspond_fk1 FOREIGN KEY(lib_activite) references activites(lib_activite),
    CONSTRAINT correspond_fk2 FOREIGN KEY(numero_N) references niveau(numero_N),
    CONSTRAINT correspond_fk3 FOREIGN KEY(code_P) references parcours(code_P)
);

CREATE TABLE semestre (
    numero_sem VARCHAR(1) NOT NULL,
    numero_N INT NOT NULL,
    CONSTRAINT semestre_pk PRIMARY KEY(numero_sem),
    CONSTRAINT semestre_fk FOREIGN KEY(numero_N)
);

CREATE TABLE ue (
    code_UE VARCHAR(7) NOT NULL,
    lib_activite VARCHAR(50) NOT NULL,
    numero_sem VARCHAR(1) NOT NULL,
    CONSTRAINT ue_pk PRIMARY KEY(code_UE),
    CONSTRAINT ue_fk1 FOREIGN KEY(lib_activite) references activites(lib_activite),
    CONSTRAINT ue_fk2 FOREIGN KEY(numero_sem) references semestre(numero_sem)
);

CREATE TABLE sae (
    code_SAE VARCHAR(7),
    lib_SAE VARCHAR(50) NOT NULL,
    nb_h_TD_enc INT NOT NULL,
    nb_h_TD_autonomie INT NOT NULL,
    CONSTRAINT sae_pk PRIMARY KEY(code_SAE)
);

CREATE TABLE ressources (
    code_R VARCHAR(7) NOT NULL,
    lib_R VARCHAR(50) NOT NULL,
    nb_h_CM_PN INT NOT NULL,
    nb_h_TD_PN INT NOT NULL,
    nb_h_TP_PN INT NOT NULL,
    numero_sem VARCHAR(1) NOT NULL,
    CONSTRAINT ressources_pk PRIMARY KEY(code_R),
    CONSTRAINT ressources_fk FOREIGN KEY(numero_sem) references semestre(numero_sem)
);

CREATE TABLE comprend_R (
    code_R VARCHAR(50),
    code_SAE VARCHAR(50),
    nb_h_TD_C INT NOT NULL,
    nb_h_TP_C INT NOT NULL
    CONSTRAINT comprend_R_pk PRIMARY KEY(code_R,code_SAE),
    CONSTRAINT comprend_R_fk1 FOREIGN KEY(code_R) references ressources(code_R),
    CONSTRAINT comprend_R_fk2 FOREIGN KEY(code_SAE) references sae(code_SAE)
);

CREATE TABLE est_enseignee(
    code_P VARCHAR(50),
    code_R VARCHAR(50),
    CONSTRAINT est_enseignee_pk PRIMARY KEY(code_P,code_R),
    CONSTRAINT est_enseignee_fk1 FOREIGN KEY(code_P) references parcours(code_P),
    CONSTRAINT est_enseignee_fk2 FOREIGN KEY(code_P) references ressources(code_R),
    CHECK COUNT(SELECT code_R from est_enseignee) <= 3 AND CHECK COUNT(SELECT code_R from est_enseignee) >= 1
);