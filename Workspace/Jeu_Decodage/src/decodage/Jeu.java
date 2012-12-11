package decodage;

import java.util.Scanner;

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
		Scanner sc=new Scanner(System.in);
		this.niveau=new Facile(this.alphaCode,this.alpha);
		System.out.println("Ma phrase mystere: "+this.niveau.encode(phrase_mystere));
		System.out.println("Saisissez une association lettre-symbole");
		String lettre=sc.nextLine();
		String symbole=sc.nextLine();
		while (1 < 2)
		{
			
			System.out.println("Saisissez une association lettre-symbole");
			lettre=sc.nextLine();
			symbole=sc.nextLine();
		}
	}
	
	public static void main(String[] args) 
	{
		// TODO Auto-generated method stub
		Jeu game=new Jeu();
		game.truc();
	}
}

