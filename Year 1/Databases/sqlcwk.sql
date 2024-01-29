/*
@Muhammad Kashif-Khan

This is an sql file to put your queries for SQL coursework. 
You can write your comment in sqlite with -- or /* * /

To read the sql and execute it in the sqlite, simply
type .read sqlcwk.sql on the terminal after sqlite3 chinook.db.
*/

/* =====================================================
   WARNNIG: DO NOT REMOVE THE DROP VIEW
   Dropping existing views if exists
   =====================================================
*/
DROP VIEW IF EXISTS vCustomerPerEmployee;
DROP VIEW IF EXISTS v10WorstSellingGenres ;
DROP VIEW IF EXISTS vBestSellingGenreAlbum ;
DROP VIEW IF EXISTS v10BestSellingArtists;
DROP VIEW IF EXISTS vTopCustomerEachGenre;

/*
============================================================================
Question 1: Complete the query for vCustomerPerEmployee.
WARNNIG: DO NOT REMOVE THE STATEMENT "CREATE VIEW vCustomerPerEmployee AS"
============================================================================
*/
CREATE VIEW vCustomerPerEmployee  AS
SELECT 
   employees.LastName,
   employees.FirstName,
   employees.EmployeeId, 
   count(customers.CustomerId) AS TotalCustomers 
FROM 
   employees 
LEFT JOIN 
   customers ON employees.EmployeeId = customers.SupportRepId 
GROUP BY 
   employees.EmployeeId;




/*
============================================================================
Question 2: Complete the query for v10WorstSellingGenres.
WARNNIG: DO NOT REMOVE THE STATEMENT "CREATE VIEW v10WorstSellingGenres AS"
============================================================================
*/
CREATE VIEW v10WorstSellingGenres  AS

SELECT 
   genres.Name AS Genre,
   IFNULL(sum(invoice_items.Quantity), 0) AS Sales
FROM
   genres
LEFT JOIN 
   tracks ON genres.GenreId = tracks.GenreId 
LEFT JOIN 
   invoice_items ON tracks.TrackId = invoice_items.TrackId 
GROUP BY 
   genres.GenreId 
ORDER BY 
   Sales ASC 
LIMIT 10;






/*
============================================================================
Question 3:
Complete the query for vBestSellingGenreAlbum
WARNNIG: DO NOT REMOVE THE STATEMENT "CREATE VIEW vBestSellingGenreAlbum AS"
============================================================================
*/
CREATE VIEW vBestSellingGenreAlbum  AS       -- THIS VIEW NEEDS OVERWRITING. The code is correct but i cannot overwrite the view

SELECT 
   genres.Name AS Genre,
   albums.Title AS Album,
   artists.Name AS Artist,
   MAX(sales_per_album.total_sales) AS Sales
FROM
   genres
LEFT JOIN 
   tracks ON genres.GenreId = tracks.GenreId 
LEFT JOIN 
   invoice_items ON tracks.TrackId = invoice_items.TrackId 
LEFT JOIN 
   albums ON tracks.AlbumId = albums.AlbumId
LEFT JOIN
   artists ON artists.ArtistId = albums.ArtistId
INNER JOIN (
   SELECT
      genres.GenreId,
      albums.AlbumId,
      SUM(invoice_items.Quantity) AS total_sales
   FROM
      genres
   LEFT JOIN 
      tracks ON genres.GenreId = tracks.GenreId 
   LEFT JOIN 
      invoice_items ON tracks.TrackId = invoice_items.TrackId 
   LEFT JOIN 
      albums ON tracks.AlbumId = albums.AlbumId
   GROUP BY
      genres.GenreId, albums.AlbumId
   HAVING
      total_sales > 0
   ORDER BY 
      genres.GenreId ASC, total_sales DESC
   ) AS sales_per_album ON albums.AlbumId = sales_per_album.AlbumId
GROUP BY 
   sales_per_album.GenreId;



/*
============================================================================
Question 4:
Complete the query for v10BestSellingArtists
WARNNIG: DO NOT REMOVE THE STATEMENT "CREATE VIEW v10BestSellingArtists AS"
============================================================================
*/

CREATE VIEW v10BestSellingArtists AS

SELECT
   artists.Name AS Artist,
   COUNT(albums.AlbumId) AS TotalAlbum,
   SUM(track_sales.total_sales) AS TotalTrackSales
FROM
   artists
LEFT JOIN
   albums ON artists.ArtistId = albums.ArtistId
LEFT JOIN (
   SELECT
      albums.AlbumId,
      SUM(invoice_items.Quantity) AS total_sales
   FROM
      albums
   LEFT JOIN 
      tracks ON tracks.AlbumId = albums.AlbumId
   LEFT JOIN 
      invoice_items ON tracks.TrackId = invoice_items.TrackId 
   GROUP BY
      albums.AlbumId
   HAVING
      total_sales > 0
   ORDER BY 
      total_sales DESC
   ) AS track_sales ON track_sales.AlbumId = albums.AlbumId
GROUP BY 
   Artist
ORDER BY 
   TotalTrackSales DESC
LIMIT 10;


/*
============================================================================
Question 5:
Complete the query for vTopCustomerEachGenre
WARNNIG: DO NOT REMOVE THE STATEMENT "CREATE VIEW vTopCustomerEachGenre AS" 
============================================================================
*/
CREATE VIEW vTopCustomerEachGenre AS

SELECT
   all_spending_per_customer.GenreName AS Genre,
   all_spending_per_customer.FirstName || ' ' || all_spending_per_customer.LastName AS TopSpender,
   MAX(all_spending_per_customer.spending_per_customer) AS TotalSpending
FROM
   invoice_items
LEFT JOIN
   invoices ON invoices.InvoiceId = invoice_items.InvoiceId
LEFT JOIN
   customers ON invoices.CustomerId = customers.CustomerId
LEFT JOIN
   tracks ON tracks.TrackId = invoice_items.TrackId
LEFT JOIN 
   genres ON tracks.GenreId = genres.GenreId
INNER JOIN (
   SELECT
      genres.Name AS GenreName,
      customers.CustomerId,
      customers.FirstName,
      customers.LastName,
      SUM(invoice_items.Quantity * invoice_items.UnitPrice) AS spending_per_customer
   FROM
      invoice_items
   LEFT JOIN
      invoices ON invoices.InvoiceId = invoice_items.InvoiceId
   LEFT JOIN
      customers ON invoices.CustomerId = customers.CustomerId
   LEFT JOIN
      tracks ON tracks.TrackId = invoice_items.TrackId
   LEFT JOIN 
      genres ON tracks.GenreId = genres.GenreId
   GROUP BY customers.CustomerId, tracks.GenreId
   ORDER BY tracks.GenreId
) AS all_spending_per_customer ON all_spending_per_customer.CustomerId = customers.CustomerId
GROUP BY Genre;


/*
To view the created views, use SELECT * FROM views;
You can uncomment the following to look at invididual views created
*/
SELECT * FROM vCustomerPerEmployee;
SELECT * FROM v10WorstSellingGenres;
SELECT * FROM vBestSellingGenreAlbum; -- i cant overwrite this view. needs overwriting 
SELECT * FROM v10BestSellingArtists;
SELECT * FROM vTopCustomerEachGenre;
