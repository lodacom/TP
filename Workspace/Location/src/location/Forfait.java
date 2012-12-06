package location;

public class Forfait extends AbstractLocation
{	
	public Forfait()
	{
		this.cout=10;
		this.duree=365;//nombre de jours
	}
	
	@Override
	public void calculCoutLocation() 
	{
		// TODO Auto-generated method stub
		
	}
	
	public int get_cout()
	{
		return this.cout;
	}

}
