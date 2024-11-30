#ifndef DOCTORPERSONALINFO_H
#define DOCTORPERSONALINFO_H

#include <string>
#include <memory>
#include <vector>

class DoctorPersonalInfo{
public:
	std::string name;
	std::string contact;
	std::string qualification;
	
	DoctorPersonalInfo();
	DoctorPersonalInfo(const std::string &name, const std::string &contact,
			   const std::string &qualification);
	void displayPersonalInfo();
	void saveToJSON(const std::string &fileName);
	static std::vector<std::shared_ptr<DoctorPersonalInfo>> loadFromJSON(const std::string &fileName);

};
#endif
