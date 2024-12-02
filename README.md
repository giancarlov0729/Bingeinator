Team Name: Great Minds Vary
Team Members: Giancarlo Vidal, Miguel Goiuzueta,Vamshidhar Kallem
Project Name: The Bingeinator
Problem: Have you ever been in a situation where you just finished a great show and have no idea what to watch next? In today’s vast and rapidly growing entertainment landscape, viewers often struggle to decide what to watch next after finishing a show they enjoyed. With hundreds of platforms and thousands of shows available at the click of a button, the sheer volume of choices can be overwhelming. Traditional recommendation systems often focus on single factors, like genre, leaving out other important elements like the influence of star actors or the vision of directors that shape a show's distinct flavor.
Motivation: Our project aims to address this gap by providing a more holistic recommendation system that not only considers the genre of the show the user has watched but also takes into account the key contributors behind it, such as the actors and directors. By leveraging a multi-dimensional approach to recommendations, we hope to create a system that provides more personalized and meaningful suggestions, helping viewers discover content they are more likely to connect with on a deeper level.
Features: In the case of our program/application, our user would input a show we would know that the “problem” is solved when our application outputs three different lists displaying similar shows via genre, actors, and director/producers.  
Data: https://www.thetvdb.com/ API 
Tools: C++, SFML, Possibly another Web-Based UI Component
Strategy: Our strategy will be to implement two different data structures with nodes representing different TV Shows containing data regarding, leading actor, producer, and genre, with each node being sorted by its rating out of ten. For these purposes we want to compare the approach of using a max binary heap to store the data compared with a splay tree. Specifically we will compare how quickly they can extract the highest rated shows for each different category. 
Distribution of Responsibilities and Roles: 
Data Structure Implementation: Giancarlo, Design and implement the max binary heap and splay tree data structures. Define the structure of nodes (leading actor, producer, genre, and rating). Implement methods for inserting, extracting, and traversing data in both structures.Collaborate with other team members to ensure integration with the overall application. 
Data Set/ API Implementation: Miguel, Clean and format the data to ensure it aligns with the attributes required for your data structures (leading actor, producer, genre, and rating). ​​Collaborate with the Data Structure and Algorithm Implementation Lead to ensure the dataset is properly structured for use in the max binary heap and splay tree. 
Performance Analysis: Vamshidhar, Develop testing frameworks to measure and compare the extraction speeds of both data structures. Analyze results and prepare documentation on the performance findings, including visualization. 

References:
https://spotifyviz.com/
https://www.thetvdb.com/


