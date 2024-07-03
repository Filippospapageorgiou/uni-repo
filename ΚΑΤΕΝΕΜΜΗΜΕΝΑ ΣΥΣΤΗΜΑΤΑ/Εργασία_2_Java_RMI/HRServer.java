import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class HRServer {
	public static void main(String[] args){
		try {
            HRImpl obj = new HRImpl();
            Registry registry = LocateRegistry.createRegistry(1099);
            registry.rebind("HotelReservation", obj);
            System.out.println("HRServer is ready.");
        } catch (Exception e) {
            System.err.println("HRServer exception: " + e.toString());
            e.printStackTrace();
        }
	}
}