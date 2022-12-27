const store = new Vuex.Store({
  state: {
    // initial state
    servers: [
      { name: "Lorem", status: true, adr: "192.168.0.24", type: "database" },
      { name: "Ipsum", status: true, adr: "192.168.0.25", type: "gear" },
      { name: "Dolor", status: true, adr: "192.168.0.26", type: "layer-group" },
      { name: "Adipiscing", status: true, adr: "192.168.0.37", type: "server" },
      { name: "Eiusmod", status: true, adr: "192.168.0.17", type: "server" },
      { name: "Cupidatat", status: true, adr: "192.168.0.23", type: "plug" },
      { name: "Reprehenderit", status: true, adr: "192.168.0.47", type: "cloud" },
      { name: "Typhoon", status: true, adr: "192.168.0.127", type: "network-wired" },
    ],
    internal: {
      status: undefined,
      self: "a",
      memory: {
        ram: "",
        rom: {
          total: "",
          avaliable: "",
        },
      },
      network: {
        ip: "",
        ip6: "",
        router: "",
        mac: "",
        gateway: "",
        sub: "",
        dns: "",
      },
    }
  },

  /*
  database
  cloud
  server
  tasks
  network-wired
  plug
  bolt
  gear
  layer-group
  */

  mutations: {
    UPDATE_SERVER_STATUS(state, payload) {
      state.servers[payload].status ^= true;
    },
    UPDATE_INTERNAL_STATUS(state, payload) {
      state.internal.self = payload.self;
      state.internal.status = payload.status;
      state.internal.memory.ram = payload.memory.ram;
      state.internal.memory.rom.total = payload.memory.rom.total;
      state.internal.memory.rom.avaliable = payload.memory.rom.avaliable;
      state.internal.network.ip = payload.network.ip;
      state.internal.network.mac = payload.network.mac;
      state.internal.network.gateway = payload.network.gateway;
      state.internal.network.dns = payload.network.dns;
    }
  },

  actions: {
    serverStatus({ commit }, server) {
      commit("UPDATE_SERVER_STATUS", server);
    },
    internalStatus({ commit }, server) {
      commit("UPDATE_INTERNAL_STATUS", server);
    }
  },
});

Vue.component("dashboard-clock", {
  props: {
    digital: {
      default: true,
      type: Boolean,
    },

    binary: {
      default: false,
      type: Boolean,
    },
  },

  data() {
    return {
      time: "",
    };
  },
  template: `
    <div class='dashboard-clock'>
        <div v-if="digital" class="dashboard-clock-digital">{{time}}</div>
        <table v-if="binary" class="dashboard-clock-binary">
            <tr class='hours'>
                <td v-for='n in 6'></td>
            </tr>
            <tr class='minutes'>
                <td v-for='n in 6'></td>
            </tr>
            <tr class='seconds'>
                <td v-for='n in 6'></td>
            </tr>
        </table>
    </div>
    `,
  mounted: function () {
    window.setInterval(this.render, 1000);
  },
  methods: {
    render() {
      const d = new Date();
      const h = d.getHours();
      const m = d.getMinutes();
      const s = d.getSeconds();

      this.time = `${this.addZero(h)} : ${this.addZero(m)} : ${this.addZero(
        s
      )}`;

      this.light(this.convert(s), ".seconds");
      this.light(this.convert(m), ".minutes");
      this.light(this.convert(h), ".hours");
    },
    convert(num) {
      let bin = "";
      let conv = [];

      while (num > 0) {
        bin = (num % 2) + bin;
        num = Math.floor(num / 2);
      }

      conv = bin.split("");

      while (conv.length < 6) {
        conv.unshift("0");
      }

      return conv;
    },
    light(array, type) {
      $(type + " td").attr("class", "num0");
      for (var i = 0; i < array.length; i++) {
        $(type + " td:eq(" + i + ")").attr("class", "num" + array[i]);
      }
    },
    addZero(i) {
      if (i < 10) {
        i = "0" + i;
      }
      return i;
    },
  },
});

Vue.component("dashboard-header", {
  props: ["title"],
  template: `
    <header class="dashboard-header">
        <h1 class="dashboard-title">{{title}}</h1>
        <slot></slot>
    </header>
    `,
});

Vue.component("server-list", {
  template: '<div class="server-list"><slot></slot></div>',
});

Vue.component("server", {
  props: ["type"],
  template: `
    <div class="server">
        <div class="server-icon fa" 
            :class="'fa-' + type">
        </div>
        <ul class="server-details">
            <li>Hostname:<slot name="name"></slot></li>                         
            <li>Status:<slot name="status"></slot></li>
            <li>Address:<slot name="adr"></slot></li>
        </ul>
    </div>`,
});

Vue.component("server-status", { 
  template: `<div class="server-list" style="padding-top: 30px;"><slot></slot></div> `
});

Vue.component("embedded-status", { 
  props: ["title"],
  template: `
    <header class="dashboard-header">
        <h1 class="dashboard-title">{{title}}</h1>
        <slot></slot>
    </header>
  `
 });

//Vue.use(Vuex);
const dashboard = new Vue({
  el: "dashboard",
  data: () => {
    return {
      servers: store.state.servers,
      internal: store.state.internal,
    };
  },

  mounted() {
    setInterval(
      async () => {
        await fetch("http://localhost:3333")
          .then((response) =>  response.json())
          .then((data) => store.dispatch("internalStatus", {
            status: data.status,
            self: data.self,
            memory: {
              ram: data.memory.ram,
              rom: {
                total: data.memory.rom.total,
                avaliable: data.memory.rom.avaliable,
              },
            },
            network: {
              ip: data.network.ip,
              mac: data.network.mac,
              gateway: data.network.gateway,
              dns: data.network.dns,
            }
          }));
        store.dispatch(
          "serverStatus",
          Math.floor(Math.random() * (this.servers.length - 0) + 0)
        );
      },
      1000
    );
  },
});
