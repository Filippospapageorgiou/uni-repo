import java.rmi.Remote;
import java.rmi.RemoteException;

public interface HRListener extends Remote {
    void 	notifyUpdate(String message) throws RemoteException;
    String 	getClientName() throws RemoteException; 
}
