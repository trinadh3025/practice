Overview of the Healthcare Management System
--------------------------------------------
This health care management system is designed to simulate the real-world operations of a hospital suing object-oriented programming principles. It provides a modular, maintainable and extensible architecture, integrating key components such as doctors, patients, departments, medical history, and appointments. The system also ensures data persistence using JSON files, making it practical for long term usage.

Detailed Class Descriptions
----------------------------
DoctorPersonalInfo

    Stores personal details about the doctor, independent of hospital-specific data.
    Examples: Name, age, contact.

Doctor

    Represents a doctor associated with a hospital.
    Attributes include specialty, availability, and a link to the personal information (DoctorPersonalInfo).
    Can be assigned to departments.

Department

    Represents a department in the hospital (e.g., Cardiology, Orthopedics).
    Contains a list of doctors specializing in treatments offered by the department.

Patient

    Represents a patient registered in the hospital.
    Maintains attributes such as contact details, treatment status, and a vector of MedicalHistory.

MedicalHistory

    Represents a record of a patient’s past treatment.
    Attributes include the name of the previous hospital, the doctor responsible for the treatment, and the treatment details.

Appointment

    Represents a scheduled meeting between a patient and a doctor.
    Includes attributes such as time slot, symptoms, and references to Patient and Doctor.

Relations Among Classes
----------------------------
Here is how the classes interact:

DoctorPersonalInfo <--> Doctor:

    Doctor has a std::shared_ptr<DoctorPersonalInfo> to represent the personal details of the doctor. This separates personal information from hospital-specific details.

MedicalHistory <--> Doctor:

    Each MedicalHistory contains a std::shared_ptr<Doctor> to indicate which doctor provided past treatments.

Patient <--> MedicalHistory:

    Patient maintains a list of MedicalHistory objects, representing their past treatments.

Appointment <--> Patient and Doctor:

    Appointment connects a Patient and a Doctor, representing a scheduled meeting between the two. It also includes other appointment-specific details, such as the time slot and symptoms.

Department <--> Doctor:

    Department contains a list of std::shared_ptr<Doctor>, representing the doctors working in that department.

[DoctorPersonalInfo]
        ↑
        | (1-to-1)
[Doctor]----------------->(1-to-many)----[Department]
        |
        | (1-to-many)
        ↓
[MedicalHistory]---------------->[Patient]
        |
        ↓ (1-to-1)
[Appointment]

UML:
---
1. Association:
    Doctor <-> Department: Departments are associated with multiple doctors.
    Doctor <-> Appointment: Doctors have appointments
    Patient <-> Appointment: Patients have appointments
2. Aggregation:
    Dcotr <-> DoctorPersonalInfo: Each doctor has one personal information object.
    Patient <-> MedicalHistory: Patients aggregate multiple medical history records
3. Dependency:
    Appointment depends on both Patient and Doctor for its functionality.
