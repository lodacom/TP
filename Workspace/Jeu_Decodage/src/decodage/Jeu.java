package decodage;

public class Jeu 
{
	public AlphabetSymbole alphaCode;
	public AlphabetLettre alpha;
	public AbstractGestPhraseMystere GPM;
	//gestionnaire de phrase mystere
	public AbstractFactory niveau;
	private String phrase_mystere;
	
	public Jeu()
	{
		this.alphaCode=new AlphabetSymbole();
		this.alpha=new AlphabetLettre();
		this.phrase_mystere="le petit chaperon rouge";
	}	
	
	public void truc()
	{
		this.niveau=new Facile(this.alphaCode,this.alpha);
		System.out.println("Ma phrase mystere: "+this.niveau.encode(phrase_mystere));
	}
	
	public static void main(String[] args) 
	{
		// TODO Auto-generated method stub
		Jeu game=new Jeu();
		game.truc();
	}
}

