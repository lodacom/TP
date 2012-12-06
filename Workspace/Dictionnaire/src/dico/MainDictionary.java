package dico;
import dico.FastDictionary;
import dico.OrderedDictionary;

public class MainDictionary {

	/**
	 * @param args
	 */
	public static void main(String[] args) 
	{
		// TODO Auto-generated method stub
		FastDictionary dico=new FastDictionary(1);
		dico.put("dark", "the absence of light");
		dico.put("God", "human prey him");
		Object truc=dico.get("God");
		System.out.println(truc);
		//........................................
		/*OrderedDictionary ordo=new OrderedDictionary(10);
		ordo.put("dark", "the absence of light");
		ordo.put("God", "human prey him");
		Object truc1=ordo.get("God");
		System.out.println(truc1);*/
	}

}
