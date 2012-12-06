package bidon;

public abstract class Commande 
{
	int volumeDeplace;
	
	public abstract void Do();
	public abstract void Undo();
}
