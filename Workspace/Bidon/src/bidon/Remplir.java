package bidon;

public class Remplir extends Commande
{
	Bidon bid;
	Jeu j;
	
	@Override
	public void Do() 
	{
		// TODO Auto-generated method stub
		int  volumeDeplace=bid.getVolume_present();
		this.bid.remplir();
	}

	@Override
	public void Undo() 
	{
		// TODO Auto-generated method stub
		this.bid.retirer();
	}

}
