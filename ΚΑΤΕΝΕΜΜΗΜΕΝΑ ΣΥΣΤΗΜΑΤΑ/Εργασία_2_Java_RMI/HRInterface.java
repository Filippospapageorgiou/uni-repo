import java.rmi.Remote;
import java.rmi.RemoteException;


public interface HRInterface extends Remote {
    String checkAvailability() throws RemoteException; 
    void addListener(HRListener listener) throws RemoteException;
    void removeListener(HRListener listener) throws RemoteException;
 	void makeReservation(String roomType, int numberOfRooms, String clientName,HRListener client) throws RemoteException; 
 	void getGuests(HRListener client) throws RemoteException;  
 	boolean CanselRes(HRListener client ,String roomType ,int numberOfRooms , String clientName) throws RemoteException;
}
