package seminaire;

public class EssaiSeminaire 
{

	/**
	 * @param args
	 */
	public static void main(String[] args) 
	{
		// TODO Auto-generated method stub	
		CycleSeminaires semin=new CycleSeminaires("","");
		while (semin.enter(null)!=8)
		{
			semin.enter(null);
		}
	}

}
