import java.rmi.server.UnicastRemoteObject;
import java.rmi.RemoteException;
import java.util.HashMap;
import java.util.Map;
import java.util.List;
import java.util.ArrayList;
import java.util.Vector;

class Reservation {
	private String clientName;
    private String roomType;
    private int numberOfRooms;
    private int totalCost;

	public Reservation(String clientName, String roomType, int numberOfRooms, int totalCost){
		this.clientName = clientName;
        this.roomType = roomType;
        this.numberOfRooms = numberOfRooms;
        this.totalCost = totalCost;
	}

	public String getClientName() {
        return clientName;
    }

    public String getRoomType() {
        return roomType;
    }

    public int getNumberOfRooms() {
        return numberOfRooms;
    }

    public int getTotalCost() {
        return totalCost;
    }

	@Override
    public String toString() {
        return "Client: " + clientName + ", Room Type: " + roomType + ", Number of Rooms: " + numberOfRooms + ", Total Cost: " + totalCost + " Euro\n";
    }
}

public class HRImpl extends UnicastRemoteObject implements HRInterface,Runnable{ 
	

	private Map<String, Integer> roomInventory;
    private Map<String, Integer> roomPrices; 
    private List<HRListener> listeners;
    private Vector<Reservation> reservations;
    

	protected HRImpl() throws RemoteException {
		super();
		roomInventory = new HashMap<>();
        roomInventory.put("A", 40);
        roomInventory.put("B", 35);
        roomInventory.put("C", 25);
        roomInventory.put("D", 30);
        roomInventory.put("E", 20);

        roomPrices = new HashMap<>(); 
        roomPrices.put("A", 75);
        roomPrices.put("B", 110);
        roomPrices.put("C", 120);
        roomPrices.put("D", 150);
        roomPrices.put("E", 200);

        listeners = new ArrayList<>();
       	reservations = new Vector<>(); 
	}


	@Override
	public synchronized String checkAvailability() throws RemoteException{
		StringBuilder availability = new StringBuilder();
		 for (Map.Entry<String, Integer> entry : roomInventory.entrySet()) {
        	String roomType = entry.getKey();
        	int availableRooms = entry.getValue();
        	int price = roomPrices.get(roomType); 
        	availability.append("Room type ").append(roomType).append(": ")
                    .append(availableRooms).append(" rooms available - price: ")
                    .append(price).append(" Euro per night\n");
    	}
        return availability.toString();
    }

    public synchronized void makeReservation(String roomType, int numberOfRooms, String clientName,HRListener client) throws RemoteException{
    	 if (roomInventory.containsKey(roomType)){
    	 	int availableRooms = roomInventory.get(roomType);
            int reservedRooms = Math.min(availableRooms, numberOfRooms);
            roomInventory.put(roomType, availableRooms - reservedRooms);
            int pricePerRoom = roomPrices.get(roomType);
            int totalCost = reservedRooms * pricePerRoom;

            String message;
              if (reservedRooms == numberOfRooms) {
                message = "Reservation successful for " + reservedRooms + " rooms of type " + roomType + " in the name of " + clientName + ". Total cost: " + totalCost + " Euro.";
            } else {
                message = "Only " + reservedRooms + " rooms of type " + roomType + " could be reserved in the name of " + clientName + ". Total cost: " + totalCost + " Euro.";
            }
             reservations.add(new Reservation(clientName, roomType, reservedRooms, totalCost));
             client.notifyUpdate(message);
             client.notifyUpdate("Subscribed to notifications for room type " + roomType);
    	 }else{
    	 	String message ="Room type " + roomType + " failed to Book Reservation\n";
    	 	client.notifyUpdate(message);
    	 }
    }

    @Override
    public void getGuests(HRListener client) throws RemoteException{
    	StringBuilder guestsList = new StringBuilder();
    	if (reservations.isEmpty()) {
            String message = "No guests have made reservations yet.";
            client.notifyUpdate(message);
        } else {
        	int count = 1;
        	for (Reservation reservation : reservations) {
            guestsList.append(count).append(". ").append(reservation.toString()).append("\n");
            count++;
        	}
        	client.notifyUpdate(guestsList.toString());
        }      	
    }

    @Override
    public boolean CanselRes(HRListener client ,String roomType ,int numberOfRooms , String clientName) throws RemoteException
    {
    	List<Reservation> remainingReservations = new ArrayList<>();
    	int roomsCancelled = 0;
    	 for (Reservation reservation : reservations){
    	 	 if (reservation.getClientName().equals(clientName) && reservation.getRoomType().equals(roomType) && roomsCancelled < numberOfRooms)
    	 	 {
    	 	 	int cancelCount = Math.min(numberOfRooms - roomsCancelled, reservation.getNumberOfRooms());
                roomsCancelled += cancelCount;
                roomInventory.put(roomType, roomInventory.get(roomType) + cancelCount);
    	 	 
    	 	 	if (reservation.getNumberOfRooms() > cancelCount) {
                	remainingReservations.add(new Reservation(clientName, roomType, reservation.getNumberOfRooms() - cancelCount, (reservation.getNumberOfRooms() - cancelCount) * roomPrices.get(roomType)));
             	}
            }else{
            	remainingReservations.add(reservation);
            }		
    	 }

    	 if(roomsCancelled > 0){

    	 	
    	 	reservations.clear();
    	 	reservations.addAll(remainingReservations);
    	 	StringBuilder result = new StringBuilder("Cancelled " + roomsCancelled + " rooms of type " + roomType + " for " + clientName + ".\nRemaining reservations:\n");
    	 	 int count = 1;
            for (Reservation reservation : remainingReservations) {
                if (reservation.getClientName().equals(clientName)) {
                    result.append(reservation.toString()).append("\n");
                }
            }
            client.notifyUpdate(result.toString());
            return true;
    	 }else{
    	 	client.notifyUpdate("No matching reservations found for cancellation.");
    	 }
    	return false; 
    }

   
    
    @Override
    public void addListener(HRListener listener) throws RemoteException {
        if (listeners == null) {
            listeners = new ArrayList<>(); 
        }
        listeners.add(listener);
        System.out.println("Client Connected: " + listener.getClientName());
    }

     @Override
    public void removeListener(HRListener listener) throws RemoteException {
        if (listeners != null) {
            listeners.remove(listener);
        }
        System.out.println("Client disconnected: " + listener.getClientName());
    }

   
    @Override
    public void run() {
        
    }

}