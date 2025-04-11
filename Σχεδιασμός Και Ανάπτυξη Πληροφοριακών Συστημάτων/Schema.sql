-- Πίνακας Προμηθευτών
CREATE TABLE Promitheftes (
    id_promithefti INT PRIMARY KEY AUTO_INCREMENT,
    eponymia VARCHAR(100) NOT NULL,
    afm VARCHAR(9) NOT NULL,
    tilefono VARCHAR(15),
    email VARCHAR(50)
);

-- Πίνακας Τιμολογίων
CREATE TABLE Timologia (
    id_timoligiou INT PRIMARY KEY AUTO_INCREMENT,
    id_promithefti INT,
    arithmos_timolodiou VARCHAR(20) NOT NULL,
    imerominia DATE NOT NULL,
    poso DECIMAL(10,2) NOT NULL,
    katastasi ENUM('Εκκρεμεί', 'Εγκρίθηκε', 'Πληρώθηκε') DEFAULT 'Εκκρεμεί',
    FOREIGN KEY (id_promithefti) REFERENCES Promitheftes(id_promithefti)
);

-- Πίνακας Πληρωμών
CREATE TABLE Pliromes (
    id_pliromis INT PRIMARY KEY AUTO_INCREMENT,
    id_promithefti INT,
    imerominia DATE NOT NULL,
    poso DECIMAL(10,2) NOT NULL,
    tropos_pliromis ENUM('Επιταγή', 'Κατάθεση', 'Μετρητά'),
    arithmos_epitagis VARCHAR(20),
    FOREIGN KEY (id_promithefti) REFERENCES Promitheftes(id_promithefti)
);

-- Πίνακας Συσχέτισης Πληρωμών-Τιμολογίων
CREATE TABLE Pliromes_Timologia (
    id_pliromis INT,
    id_timoligiou INT,
    poso DECIMAL(10,2) NOT NULL,
    PRIMARY KEY (id_pliromis, id_timoligiou),
    FOREIGN KEY (id_pliromis) REFERENCES Pliromes(id_pliromis),
    FOREIGN KEY (id_timoligiou) REFERENCES Timologia(id_timoligiou)
);