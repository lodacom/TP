package location;

import java.util.Random;

public abstract class AbstractLocation 
{
	public int cout;
	public int duree;
	public int cout_blue_ray=3;
	public int cout_dvd=2;
	public int duree_emprunt;
	
	public AbstractLocation()
	{
		Random r=new Random();
		this.duree_emprunt=r.nextInt(6);
	}
	
	public abstract void calculCoutLocation();
}
