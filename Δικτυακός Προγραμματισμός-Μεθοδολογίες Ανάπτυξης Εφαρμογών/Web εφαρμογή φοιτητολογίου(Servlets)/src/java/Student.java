/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author filip
 */
public class Student {
    private String name;
    private String surname;
    private String school;
    private int semester;
    private int passed;

    public Student() {
    }

    public Student(String name, String surname, String school, int semester, int paased) {
        this.name = name;
        this.surname = surname;
        this.school = school;
        this.semester = semester;
        this.passed = paased;
    }

    public String getName() {
        return name;
    }

    public String getSurname() {
        return surname;
    }

    public String getSchool() {
        return school;
    }

    public int getSemester() {
        return semester;
    }

    public int getPassed() {
        return passed;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }

    public void setSchool(String school) {
        this.school = school;
    }

    public void setSemester(String semester) {
        this.semester = Integer.parseInt(semester);
    }

    public void setPassed(String passed) {
        this.passed = Integer.parseInt(passed);
    }
    
    
}
