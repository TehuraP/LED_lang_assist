{
  let englishWord = "";
  let germanWord = "";
  templateEnglishWord = "";
  templateGermanWord = "";
  document.addEventListener("DOMContentLoaded", refreshPage);

  function refreshPage() {
    fetch("http://192.168.0.221/get_words.php") // URL to the PHP script
      .then((response) => response.json())
      .then((data) => {
        console.log(data);
        console.log(templateEnglishWord); // For debugging
        // Update the HTML with data
        // document.getElementById('json-data').textContent = JSON.stringify(data, null, 2);
        englishWord = data.English.replace(
          data.English[0],
          data.English[0].toUpperCase()
        );

        germanWord = data.Deutsch.replace("^", "ö")
          .replace("_", "ü")
          .replace("`", "ß")
          .replace(data.Deutsch[0], data.Deutsch[0].toUpperCase());
         
        templateGermanWord = document.getElementById("germanWord");
        templateEnglishWord = document.getElementById("englishWord");
        if(germanWord.includes('Der ')) {
            templateGermanWord.classList.add('der')
        }
        else {
            templateGermanWord.classList.remove('der')
        }
        if(germanWord.includes('Die ')) {
            templateGermanWord.classList.add('die')
        }
        else {
            templateGermanWord.classList.remove('die')
        }
        if(germanWord.includes('Das ')) {
            templateGermanWord.classList.add('das')
        }
        else {
            templateGermanWord.classList.remove('das')
        }

        templateGermanWord.textContent = germanWord;
        templateEnglishWord.textContent = englishWord;
      })
      .catch((error) => console.error("Error fetching data:", error));
  }
}
