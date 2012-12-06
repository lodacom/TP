package seminaire;

import javax.swing.Timer;

public class Creneau 
{
	public Timer debut;
	
	public Creneau(int p_temps)
	{
		debut=new Timer(p_temps,null);
	}
}
