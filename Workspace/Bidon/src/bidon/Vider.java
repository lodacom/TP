package bidon;

public class Vider extends Commande
{
	Bidon bid;
	Jeu j;
	
	@Override
	public void Do() 
	{
		// TODO Auto-generated method stub
		int  volumeDeplace=bid.getVolume_present();
		this.bid.vider();
	}

	@Override
	public void Undo() 
	{
		// TODO Auto-generated method stub
		this.bid.ajouter();
	}

}
