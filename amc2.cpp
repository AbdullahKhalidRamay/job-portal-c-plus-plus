#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Function to create a new company file
void createCompanyFile(const string& companyName) {
    ofstream file((companyName + ".txt").c_str(), ios::app);
    if (file.is_open()) {
        file << "Applicant Details:\n";
        file.close();
        cout << "Company file '" << companyName << ".txt' created." << endl;
    } else {
        cout << "Error creating company file." << endl;
    }
}

// Function to display available companies
void displayCompanies() {
    ifstream filesList("files_list.txt");
    if (filesList.is_open()) {
        string companyName;
        int count = 1;
        while (getline(filesList, companyName)) {
            cout << count << ". " << companyName << endl;
            count++;
        }
        filesList.close();
    } else {
        cout << "Error displaying available companies." << endl;
    }
}

// Function to add  details for a company
void addCompanyDetails(const string& companyName) {
    ofstream file((companyName + ".txt").c_str(), ios::app);
    if (file.is_open()) {
        string companyDetails;
        cout << "Enter  details for " << companyName << " (type 'exit' to finish):" << endl;
        while (true) {
            getline(cin, companyDetails);
            if (companyDetails == "exit") {
                break;
            }
            file << companyDetails << endl;
        }
        file.close();
        cout << "Additional details added for " << companyName << "." << endl;
    } else {
        cout << "Error adding details for " << companyName << "." << endl;
    }
}
void displayCandidateDetails(const string& companyName, const string& applicantName,
                              const string& applicantGender, const string& applicantContactNo,
                              const string& applicantEmail, const string& applicantEducation,
                              const string& applicantExperience) {
    cout << "\nCandidate Details for " << companyName << ":" << endl;
    cout << "Name: " << applicantName << "\nGender: " << applicantGender
         << "\nContact No: " << applicantContactNo << "\nEmail: " << applicantEmail
         << "\nEducation: " << applicantEducation << "\nExperience: " << applicantExperience << "\n";
}
void applyForJob(const string& companyName) {
    ifstream companyFile((companyName + ".txt").c_str());
    if (companyFile.is_open()) {
        string line;
        cout << "Details for " << companyName << ":" << endl;
        while (getline(companyFile, line)) {
            cout << line << endl;
        }
        companyFile.close();
    } else {
        cout << "Error displaying company details." << endl;
        return;
    }
  // Prompt for candidate details
    string applicantName, applicantEmail, applicantExperience, applicantGender, applicantEducation, applicantContactNo;
    cout << "\nEnter your name: ";
    cin.ignore();
    getline(cin, applicantName);
    cout << "Enter your gender: ";
    getline(cin, applicantGender);
    cout << "Enter your contact no: ";
    getline(cin, applicantContactNo);
    cout << "Enter your email: ";
    getline(cin, applicantEmail);
    cout << "Enter your Education: ";
    getline(cin, applicantEducation);
    cout << "Enter your experience: ";
    getline(cin, applicantExperience);

    // Save candidate details to the company file
    ofstream file;
    file.open((companyName + ".txt").c_str(), ios::app);
    if (file.is_open()) {
        file << "\nCandidate Details:\n";
        file << "Name: " << applicantName << ", gender: " << applicantGender
             << ", contact no: " << applicantContactNo << ", Email: " << applicantEmail
             << ", Education: " << applicantEducation << ", Experience: " << applicantExperience << "\n";
        file.close();

        // Display candidate details after saving
        displayCandidateDetails(companyName, applicantName, applicantGender, applicantContactNo,
                                applicantEmail, applicantEducation, applicantExperience);

        cout << "Application submitted." << endl;
    } else {
        cout << "Error applying for job." << endl;
    }
}

// Function to apply for a job and store applicant details

int main() {
    while (true) {
        cout << "\nWhat would you like to do?" << endl;
        cout << "1. Create a new company" << endl;
        cout << "2. Add details for a company" << endl;
        cout << "3. Apply for a job" << endl;
        cout << "4. Display available companies" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string companyName;
                cout << "Enter the company name: ";
                cin >> companyName;

                createCompanyFile(companyName);

                ofstream filesList("files_list.txt", ios::app);
                if (filesList.is_open()) {
                    filesList << companyName << endl;
                    filesList.close();
                } else {
                    cout << "Error updating files list." << endl;
                }
                break;
            }
            case 2: {
                displayCompanies();
                int companyIndex;
                cout << "Enter the number of the company you want to add details to: ";
                cin >> companyIndex;

                ifstream filesList("files_list.txt");
                if (filesList.is_open()) {
                    vector<string> companies;
                    string companyName;
                    while (getline(filesList, companyName)) {
                        companies.push_back(companyName);
                    }
                    filesList.close();

                    if (companyIndex > 0 && companyIndex <= companies.size()) {
                        addCompanyDetails(companies[companyIndex - 1]);
                    } else {
                        cout << "Invalid company selection." << endl;
                    }
                } else {
                    cout << "Error adding details for company." << endl;
                }
                break;
            }
            case 3: {
                displayCompanies();
                int companyIndexApply;
                cout << "Enter the number of the company you want to apply to: ";
               
                cin >> companyIndexApply;

                ifstream filesListApply("files_list.txt");
                if (filesListApply.is_open()) {
                    vector<string> companies;
                    string companyName;
                    while (getline(filesListApply, companyName)) {
                        companies.push_back(companyName);
                    }
                    filesListApply.close();

                    if (companyIndexApply > 0 && companyIndexApply <= companies.size()) {
                        applyForJob(companies[companyIndexApply - 1]);
                    } else {
                        cout << "Invalid company selection." << endl;
                    }
                } else {
                    cout << "Error applying for job." << endl;
                }
                break;
            }
            case 4:
                displayCompanies();
                break;
            case 5:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}

