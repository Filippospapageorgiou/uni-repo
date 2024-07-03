import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Scanner;




public class HRClient extends UnicastRemoteObject implements HRListener { 

	
    private String clientName;

	protected HRClient(String clientName) throws RemoteException {
        super();
        this.clientName = clientName;
    }

    @Override
    public void notifyUpdate(String message) throws RemoteException {
        System.out.println("Notification:\n" + message);
    }

    @Override
    public String getClientName() throws RemoteException {
        return clientName;
    }


	public static void main(String[] args){

		Scanner scanner = new Scanner(System.in);


		try{
			if (args.length == 0) {
            	printUsage();
           		return;
        	}

        	if (args.length == 2 && args[0].equals("list")) {		
        		Registry registry = LocateRegistry.getRegistry("localhost");
           		HRInterface stub = (HRInterface) registry.lookup("HotelReservation");
           		HRClient client = new HRClient(args[1]);
           		stub.addListener(client);

            	String availability = stub.checkAvailability();
            	System.out.println(availability); 
            	
            	scanner.nextLine();
            	stub.removeListener(client);     	
            	return;
        	}
        	if (args.length == 5 && args[0].equals("book")) {
                Registry registry = LocateRegistry.getRegistry("localhost");
           		HRInterface stub = (HRInterface) registry.lookup("HotelReservation");
           		HRClient client = new HRClient(args[1]);
           		stub.addListener(client);
           		stub.makeReservation(args[2], Integer.parseInt(args[3]),args[4],client);

           	
            	scanner.nextLine();
            	stub.removeListener(client);  
                return;
            }
            if (args.length == 2 && args[0].equals("guests")) {
                Registry registry = LocateRegistry.getRegistry("localhost");
           		HRInterface stub = (HRInterface) registry.lookup("HotelReservation");
           		HRClient client = new HRClient(args[1]);
           		stub.addListener(client);
           		stub.getGuests(client);

           		
            	scanner.nextLine();
            	stub.removeListener(client);  
                return;
            }
            if (args.length == 5 && args[0].equals("cancel")) {
                Registry registry = LocateRegistry.getRegistry("localhost");
           		HRInterface stub = (HRInterface) registry.lookup("HotelReservation");
           		HRClient client = new HRClient(args[1]);
           		stub.addListener(client);
           		stub.CanselRes(client,args[2],Integer.parseInt(args[3]),args[4]);

           
           		scanner.nextLine();
            	stub.removeListener(client);  
                return;
            }

		}catch (Exception e) {
            System.err.println("HRClient exception: " + e.toString());
            e.printStackTrace();
        }
	}

	private static void printUsage() {
        System.out.println("Usage:");
        System.out.println("java HRClient");
        System.out.println("java HRClient list <hostname>");
        System.out.println("java HRClient book <hostname> <type> <number> <name>");
        System.out.println("java HRClient cancel <hostname> <type> <number> <name>");
        System.out.println("java HRClient guests <hostname>");
    }

}