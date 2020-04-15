

var app = new Vue({
    el: '#app',
    data: {
      file_loaded: false,
      report: {},
    },
    methods: {
      reset() {
        this.report = {};
        this.file_loaded = false;
      },
      selectedFile() {
        console.log("Selected a val3dity report JSON file...");
        console.log(this.$refs.reportFile.files[0]);

        let file = this.$refs.reportFile.files[0];
        if (!file || file.type != "application/json")
        {
          console.log("This is not a val3dity report JSON file. Abort.");
          return;
        }

        let reader = new FileReader();
        reader.readAsText(file, "UTF-8");
        reader.onload = evt => {
          jre = JSON.parse(evt.target.result);
          this.report = jre;
          this.file_loaded = true;
        }
      }
    }
})

Vue.config.devtools = true